#include "../Headers/Socket.h"

int sock;

int init(){
    
    struct sockaddr_in server;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        return 0;
    }
    server.sin_family = AF_INET; 
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server.sin_zero),8);
    if (bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
        return 0;
    }
    listen(sock, 100);
    return 1;
}

clientDetails acceptClient(){

    int clilen;
    clientDetails c = { .sock = -1 };
    struct sockaddr_in client;
    int csock = accept(sock, (struct sockaddr*) &client, &clilen);
    if (csock < 0){
        return c;
    }
    c.sock = csock;
    c.client = client;
    return c;
}

int givefile(int filehandle, int size){
    char data[CHUNK_SIZE] = {0};

    while(fgets(data, CHUNK_SIZE, filehandle)!=NULL)
    {
        if(send(socket, data, sizeof(data), 0)== -1)
        {
            return 0;
        }
        bzero(data, CHUNK_SIZE);
    }

    return 1;
}

