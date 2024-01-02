#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define CHUNK_SIZE 1024

void printFiles(int sockfd, char* dirname, char* uname);
int uploadFile(int sockfd, char* filename, char* dirname, char* uname);
int makeDir(int sockfd, char* dirname, char* tdirname, char* uname);
int changeDir(int sockfd, char* dirname, char* tdirname, char* uname);
int deleteDir(int sockfd, char* dirname, char* tdirname, char* uname);
int deleteFile(int sockfd, char* dirname, char* filename, char* uname);
int downloadFile(int sockfd, char* dirname, char* filename, char* uname);