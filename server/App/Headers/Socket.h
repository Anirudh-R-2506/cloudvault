#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>     

#include <fcntl.h>
#define PORT 6677
#define CHUNK_SIZE 1024

typedef struct clientDetails{
    int sock;
    struct sockaddr_in client;
} clientDetails;

int init();
clientDetails acceptClient();
int givefile(int filehandle, int size);