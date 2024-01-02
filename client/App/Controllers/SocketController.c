#include "../Headers/Socket.h"

int conn(){
    
    int sock;
    struct sockaddr_in server;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        return 0;
    }
    server.sin_family=AF_INET; 
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr =inet_addr("127.0.0.1");
    int c = connect(sock, (struct sockaddr*) &server, sizeof(server));
    if (c < 0){
        return 0;
    }
    return sock;
}