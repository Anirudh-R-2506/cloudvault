#include "../Headers/User.h"
#include "../Headers/Socket.h"

char* signin(){
    
    static char un[500];
    static char pw[500];
    printf("\n\n|+++------------------------------------------------------------------+++|\n");
    printf("|+++-------------------------------LOGIN------------------------------+++|\n");
    printf("|                            USER NAME :                                 |\n");
    printf("|                                       ");
    scanf("%s",un);
    printf("|                            PASSWORD :                                  |\n");
    printf("|                                      ");
    scanf("%s",pw);
    printf("\n[-] Logging in...");
    int sock = conn();
    int ch = 2;
    write(sock, &ch, sizeof(ch));
    write(sock, un, sizeof(un));
    write(sock, pw, sizeof(pw));
    int r;
    read(sock, &r, sizeof(r));    
    if (r == -1){
        printf("\n[-] Username does not exist. Try again...\n");
        return un;
    }
    else if (r == 0){
        printf("\n[-] We're unable to accomodate you now. Please try later...\n");
        return un;
    }
    else {        
        printf("\n[-] Welcome back to CloudVault!!!\n\n");
        return un;
    }
}

char* signup(){    

    char fn[500], ln[500], pw[500];
    char* un = malloc(500 * sizeof(char));
    printf("\n\n|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------SIGNUP------------------------------+++|\n");
    printf("|                            FIRST NAME :                                |\n");
    printf("|                                        ");
    scanf("%s",fn);
    printf("|                            LAST NAME :                                 |\n");
    printf("|                                       ");
    scanf("%s",ln);
    printf("|                            USER NAME :                                 |\n");
    printf("|                                       ");
    scanf("%s",un);
    printf("|                            PASSWORD :                                  |\n");
    printf("|                                      ");
    scanf("%s",pw);
    printf("|+++-------------------THANK YOU FOR REGISTRATION---------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("\n[-] Registering user...");

    userDetails usr;
    strcpy(usr.uname, un);
    strcpy(usr.fname, fn);
    strcpy(usr.lname, ln);
    strcpy(usr.phash, pw);

    int sock = conn();
    int ch = 1;
    write(sock, &ch, sizeof(ch));
    write(sock, &usr, sizeof(usr));
    int r;
    read(sock, &r, sizeof(r));    
    if (r){
        printf("\n[-] Welcome to CloudVault!!!\n");
        return un;
    }
    else if (r == -1){
        printf("\n[-] Username already taken. Try again...\n");
        return "";
    }
    else {
        printf("\n[-] We're unable to accomodate you now. Please try later...\n");
        return "";
    }
}