#include "../Headers/Socket.h"
#include "../Headers/File.h"

void printFiles(int sockfd, char* dirname, char* uname){
    
    char cmd[500] = "cd /Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(cmd, uname);
    if (strlen(dirname) > 0){
        strcat(cmd, "/");
        strcat(cmd, dirname);
    }
    strcat(cmd, " && ls");
    FILE *fp;
    char tpath[2048];
    char path[1024];
    fp = popen(cmd, "r");
    if (fgets(path, sizeof(path), fp) != NULL){
        sprintf(tpath, "%s\n%s", tpath, path);
    }
    pclose(fp);    
    if (write(sockfd, tpath, sizeof(tpath)) < 0){
        printf("[-]Error writing to socket\n");
        return;
    }
    return;

}

int uploadFile(int sockfd, char* filename, char* dirname, char* uname){
    
    int n; 
    FILE *fp;
    char buffer[CHUNK_SIZE];

    char dir[500] = "/Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(dir, uname);    
    strcat(dir, "/");
    strcat(dir, filename);
    fp = fopen(dir, "wb+");
    if(fp==NULL)
    {
        printf("[-]Error in creating file: %s\n", dir);
        return 0;
    }
    int c = 0;
    while(1)
    {
        c++;
        if(recv(sockfd, buffer, CHUNK_SIZE, 0) < 0)
        {
            return 0;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, CHUNK_SIZE);
    }
    return 1;
}

int makeDir(int sockfd, char* dirname, char* tdirname, char* uname){
    
    char cmd[500] = "mkdir /Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(cmd, uname);
    if (strlen(dirname) > 0){
        strcat(cmd, "/");
        strcat(cmd, dirname);
    }
    strcat(cmd, "/");
    strcat(cmd, tdirname);
    if (system(cmd) < 0){
        printf("[-]Error creating directory: %s\n", cmd);
        return 0;
    }
    return 1;
}

int changeDir(int sockfd, char* dirname, char* tdirname, char* uname){

    char cmd[500] = "ls /Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(cmd, uname);
    if (strlen(dirname) > 0){
        strcat(cmd, "/");
        strcat(cmd, dirname);
    }
    strcat(cmd, "/");
    strcat(cmd, tdirname);
    if (system(cmd) < 0){
        return 0;
    }
    return 1;
}

int deleteDir(int sockfd, char* dirname, char* tdirname, char* uname){

    char cmd[500] = "rmdir /Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(cmd, uname);
    if (strlen(dirname) > 0){
        strcat(cmd, "/");
        strcat(cmd, dirname);
    }
    strcat(cmd, "/");
    strcat(cmd, tdirname);
    if (system(cmd) < 0){
        printf("[-]Error deleting directory: %s\n", cmd);
        return 0;
    }
    return 1;
}

int deleteFile(int sockfd, char* dirname, char* filename, char* uname){
    char cmd[500] = "rm /Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(cmd, uname);
    if (strlen(dirname) > 0){
        strcat(cmd, "/");
        strcat(cmd, dirname);
    }
    strcat(cmd, "/");
    strcat(cmd, filename);
    if (system(cmd) < 0){
        printf("[-]Error deleting file: %s\n", cmd);
        return 0;
    }
    return 1;
}

int downloadFile(int sockfd, char* dirname, char* filename, char* uname){

    char dir[500] = "/Users/anirudhr/Desktop/sem5/sem5_labs/cnlab/cloudvault/server/App/Storage/";
    strcat(dir, uname);    
    strcat(dir, "/");
    strcat(dir, filename);

    FILE *fp = fopen(dir, "rb");
    if(fp == NULL)
    {
        printf("[-]Error in reading file: %s\n", dir);
        return 0;
    }
    char data[CHUNK_SIZE] = {0};

    while(fgets(data, CHUNK_SIZE, fp)!=NULL)
    {
        if(send(sockfd, data, sizeof(CHUNK_SIZE), 0)== -1)
        {
            printf("[-] Error in sending file: %s\n", dir);
            exit(1);
        }
        bzero(data, CHUNK_SIZE);
    }
}