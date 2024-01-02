#include "../Headers/User.h"

int login(char* uname, char* pwd){
    
    userDetails usr = getUser(uname);  

    if (strlen(usr.uname) == 0){
        return -1;
    }    
    
    if (strcmp(str2md5(pwd), usr.phash) != 0){
        printf("User: %s\n[-] Attempted login - Incorrect password\n", usr.uname);
        return 0;
    }

    return 1;
}

int registerUsr(userDetails usr){
    char* hash = str2md5(usr.phash);
    memset(usr.phash, 0, sizeof(usr.phash));
    strcpy(usr.phash, hash);
    int r = addUser(usr);
    if (r != 1){
        printf("Unable to add new user (%s, %s, %s)", usr.uname, usr.fname, usr.lname);
    }
    char cmd[600] = "mkdir /Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(cmd, usr.uname);
    cmd[strlen(cmd)] = '\0';
    system(cmd);
    return r;
}