#include "../Headers/User.h"

#define DB "/Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Database/db.dat"
#define MAX_LENGTH 256

char* slice(char * str, size_t start, size_t end)
{
    static char buffer[2048];
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;

    return buffer;
}

char* str2md5(const char *str) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);
    int length = strlen(str);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 32, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

userDetails getUser(char* uname){
    FILE *f = fopen(DB, "r");
    char buffer[MAX_LENGTH];    
    char rec_uname[500];
    userDetails usr;

    while (fgets(buffer, MAX_LENGTH, f)){
        buffer[strcspn(buffer, "\n")] = 0;
        char buff2[MAX_LENGTH];
        strcpy(buff2, buffer);
        strcpy(rec_uname, strtok(buff2, ";"));
        if (strcmp(rec_uname, uname) == 0){
            strcpy(usr.uname, rec_uname);
            strcpy(buff2, slice(buffer, strlen(usr.uname) + 1, strlen(buffer) - 1));
            strcpy(usr.fname, strtok(buff2, ";"));
            strcpy(buff2, slice(buffer, strlen(usr.uname) + 1 + strlen(usr.fname) + 1, strlen(buffer) - 1));
            strcpy(usr.lname, strtok(buff2, ";"));
            strcpy(buff2, slice(buffer, strlen(usr.uname) + 1 + strlen(usr.fname) + 1 + strlen(usr.lname) + 1, strlen(buffer) - 1));
            strcpy(usr.phash, strtok(buff2, ";"));
            return usr;
        }
    }
    
    return usr;
}

int addUser(userDetails usr){    
    FILE *f = fopen(DB, "a+");
    if (f == NULL){
        return 0;
    }
    if (fprintf(f, "%s;%s;%s;%s\n", usr.uname, usr.fname, usr.lname, usr.phash) < 0){
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1; 
}
