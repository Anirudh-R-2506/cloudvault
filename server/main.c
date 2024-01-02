#include "App/Headers/Main.h"

int main(){
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++-----------------------WELCOME TO CLOUDVAULT----------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("\n\n\n[-] Starting server...\n");

    if (! init()){
        printf("[-] ERR: Unable to create socket. Try again.\n");
        exit(-1);
    }

    printf("[-] Socket created. Waiting for clients...\n");
    while(1){
        clientDetails cli = acceptClient();
        if (cli.sock < 0){
            printf("[-] Unable to accept client...");
            break;
        }
        if (fork() == 0){
            int ch;
            if (read(cli.sock, &ch, sizeof(ch)) < 0){
                exit(-1);
            }
            switch(ch){
                case 1:
                {
                    userDetails usr;
                    read(cli.sock, &usr, sizeof(usr));                
                    int r = registerUsr(usr);
                    write(cli.sock, &r, sizeof(r));
                    break;
                }
                case 2:
                {
                    char uname[500], pwd[500];
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, pwd, sizeof(pwd));
                    int r = login(uname, pwd);
                    write(cli.sock, &r, sizeof(r));
                    break; 
                }       
                case 3:
                {
                    char uname[500], dirname[500];
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    printFiles(cli.sock, dirname, uname);
                    break;
                }
                case 4:
                {
                    char uname[500], dirname[500], fname[500];
                    read(cli.sock, fname, sizeof(fname));
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    int r = uploadFile(cli.sock, fname, dirname, uname);
                    /* write(cli.sock, &r, sizeof(r)); */
                    break;
                }
                case 5:
                {
                    char uname[500], dirname[500], fname[500];                    
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    read(cli.sock, fname, sizeof(fname));
                    int r = makeDir(cli.sock, dirname, fname, uname);
                    write(cli.sock, &r, sizeof(r));
                    break;
                }
                case 6:
                {
                    char uname[500], dirname[500], fname[500];                    
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    read(cli.sock, fname, sizeof(fname));
                    int r = deleteDir(cli.sock, dirname, fname, uname);
                    write(cli.sock, &r, sizeof(r));
                    break;
                }
                case 7:
                {
                    char uname[500], dirname[500], fname[500];                    
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    read(cli.sock, fname, sizeof(fname));
                    int r = deleteFile(cli.sock, dirname, fname, uname);
                    write(cli.sock, &r, sizeof(r));
                    break;
                }
                case 8:
                {
                    char uname[500], dirname[500], fname[500];                    
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    read(cli.sock, fname, sizeof(fname));
                    int r = downloadFile(cli.sock, dirname, fname, uname);
                    write(cli.sock, &r, sizeof(r));
                    break;
                }
                case 9:
                {
                    char uname[500], dirname[500], fname[500];                    
                    read(cli.sock, uname, sizeof(uname));
                    read(cli.sock, dirname, sizeof(dirname));
                    read(cli.sock, fname, sizeof(fname));
                    int r = changeDir(cli.sock, dirname, fname, uname);
                    write(cli.sock, &r, sizeof(r));
                    break;
                }
            }
        }
        else{
            
        }
    }
}