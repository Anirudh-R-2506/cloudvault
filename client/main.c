#include "App/Headers/Main.h"

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

int interface() {
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++-----------------------WELCOME TO CLOUDVAULT----------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|                                                                        |\n");
    printf("|                                                                        |\n");
    printf("|                                                                        |\n");
    printf("|               PRESS 1 : >>>>>> |           SIGNUP         |            |\n");
    printf("|               PRESS 2 : >>>>>> |           SIGNIN         |            |\n");
    printf("|               PRESS 3 : >>>>>> |           TO QUIT        |            |\n");
    printf("|                                                                        |\n");
    printf("|                                                                        |\n");
    printf("|                                                                        |\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    int in ;
    printf("\n\n[-] Enter your choice: ");
    scanf("%d", & in);
    if (in == 3)
        exit(0);
    else if (in == 1 || in == 2)
        return in;
    else {
        printf("\nINVALID OPTION\n\n");
        return interface();
    }
}

int appWindow(){    
    printf("|+++--------------------------ENTER YOUR CHOICE-----------------------+++|\n");
    printf("1. UPLOAD FILE\n2. DOWNLOAD FILE\n3. DELETE FILE \n4. CD \n5. MKDIR \n6. RMDIR \n7. QUIT \n");
    int in;
    scanf("%d", &in);
    if (in == 7)
        exit(0);
    else if (in >= 1 && in <= 6)
        return in;
    else
        return appWindow();
}

int main(){

    int ch;
    char uname[500];
    while (1){
        ch = interface();
        switch (ch)
        {
            case 1:
                strcpy(uname, signup());
                break;
            case 2:
                strcpy(uname, signin());
                break;
            case 3:
                exit(0);
        }
        if (strlen(uname) != 0){
            break;
        }
    }
    char dir[500] = "";
    while (1){
        printf("Current directory: /%s\n", dir);
        int sock = conn();    
        int ch = 3;
        write(sock, &ch, sizeof(ch));
        write(sock, uname, sizeof(uname));
        write(sock, dir, sizeof(dir));
        char filelist[2048];
        read(sock, filelist, sizeof(filelist));
        printf("\nFiles in PWD\n%s\n",filelist);
        ch = appWindow();
        switch(ch){
            case 1:
            {
                char filename[500];
                char temp;scanf("%c", &temp);
                printf("[-] Enter full path to the file to upload: ");                
                scanf("%s", filename);
                FILE *fp;
                fp = fopen(filename, "rb");
                if (fp == NULL){
                    printf("[-] Unable to open file %s\n", filename);
                    return 0;
                }
                int sock = conn();
                int ch = 4;
                if (filename[(strlen(filename) - 1)] == '/')
                    filename[(strlen(filename) - 1)] = '\0';
                char fn[500];
                if (sizeof(strrchr(filename, '/')) > 0){
                    strcpy(fn, strrchr(filename, '/'));
                    strcpy(fn, slice(fn, 1, strlen(fn)));
                }
                else{
                    strcpy(fn, filename);
                }
                write(sock, &ch, sizeof(ch));
                write(sock, fn, sizeof(fn));
                write(sock, uname, sizeof(uname));
                write(sock, dir, sizeof(dir));

                char data[CHUNK_SIZE] = {0};

                while(fgets(data, CHUNK_SIZE, fp)!=NULL)
                {
                    if(send(sock, data, sizeof(data), 0)== -1)
                    {
                        printf("[-] Error in sending file %s\n", filename);
                        return 0;
                    }
                    bzero(data, CHUNK_SIZE);
                }

                printf("[-] Succesfully uploaded file %s\n", filename);
                break;
            }
            case 2:
            {
                /*tdname == filename*/
                char tdname[500];
                printf("[-] Enter name of the file to download: ");
                scanf("%s", tdname);
                int sock = conn();
                int n, ch = 8;
                write(sock, &ch, sizeof(ch));
                write(sock, uname, sizeof(uname));
                write(sock, dir, sizeof(dir));
                write(sock, tdname, sizeof(tdname));

                int r;
                read(sock, &r, sizeof(r));
                if (r <= 0){
                    printf("[-] File %s doesn't exist in current directory\n", tdname);
                    break;
                }

                FILE *fp = fopen(tdname, "wb+");
                char buffer[CHUNK_SIZE];
                if(fp==NULL)
                {
                    printf("[-]Error in creating file: %s\n", tdname);
                    break;
                }
                while(1)
                {
                    if (recv(sock, buffer, CHUNK_SIZE, 0) == -1)
                        break;
                    fprintf(fp, "%s", buffer);
                    bzero(buffer, CHUNK_SIZE);
                }                
                printf("[-] Succesfully downloaded file\n");
                break;
            }
            case 3:
            {                
                char tdname[500];
                printf("[-] Enter name of file to delete: ");
                scanf("%s", tdname);
                int sock = conn();
                int ch = 7;
                write(sock, &ch, sizeof(ch));
                write(sock, uname, sizeof(uname));
                write(sock, dir, sizeof(dir));
                write(sock, tdname, sizeof(tdname));
                int r;
                read(sock, &r, sizeof(r));
                if (r <= 0){
                    printf("[-] Unable to delete file: %s\n", tdname);
                }
                break;
            }
            case 4:
            {
                char tdname[500];
                printf("[-] Enter directory to change to: ");
                scanf("%s", tdname);                
                int sock = conn();
                int ch = 9;
                write(sock, &ch, sizeof(ch));
                write(sock, uname, sizeof(uname));
                write(sock, dir, sizeof(dir));
                write(sock, tdname, sizeof(tdname));
                int r;
                read(sock, &r, sizeof(r));
                if (r == 1){
                    strcpy(dir, tdname);
                }
                else{
                    printf("[-] Unable to change directory. Please check if directory is accesible from pwd\n");
                }
                break;
            }
            case 5:
            {
                char tdname[500];
                printf("[-] Enter name of directory to create: ");
                scanf("%s", tdname);
                int sock = conn();
                int ch = 5;
                write(sock, &ch, sizeof(ch));
                write(sock, uname, sizeof(uname));
                write(sock, dir, sizeof(dir));
                write(sock, tdname, sizeof(tdname));
                int r;
                read(sock, &r, sizeof(r));
                if (r <= 0){
                    printf("[-] Unable to create %s directory\n", tdname);
                }
                break;
            }
            case 6:
            {
                char tdname[500];
                printf("[-] Enter name of directory to delete: ");
                scanf("%s", tdname);
                int sock = conn();
                int ch = 6;
                write(sock, &ch, sizeof(ch));
                write(sock, uname, sizeof(uname));
                write(sock, dir, sizeof(dir));
                write(sock, tdname, sizeof(tdname));
                int r;
                read(sock, &r, sizeof(r));
                if (r <= 0){
                    printf("[-] Unable to delete %s directory. Make sure directory is empty first\n", tdname);
                }
                break;
            }
            case 7:
            {
                exit(0);
            }
        }
    }
    return 0;
}