#include "protocol.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "stdbool.h"
#include "string.h"
#include "unistd.h"
#define MAXBUFF 1000

int main(void){

    int listenfd, connfd;
    
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;

    char buff[MAXBUFF];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1){
        fprintf(stderr, "Error with init socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(720);

    if (bind(listenfd,  (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        fprintf(stderr, "Error while binding socket");
        return -1;
    }

    if (listen(listenfd, 3) == -1){
        fprintf(stderr, "Error while trying to LISTEN socket");
        return -1;
    }
    UserData user;
    
    while (true){
        len = sizeof(cliaddr);
        connfd = accept(listenfd,  (struct sockaddr *)&cliaddr, &len);
        if (connfd == -1){
            fprintf(stderr, "ACK Error");
            continue;
        }
        printf("connection from %s, port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));

        if (recv(connfd, &user, sizeof(user), 0) > 0){
            printf("Server got data Succesfully: UserData->x = %d, UserData->y = %d\n", user.x, user.y);
        }

        close(connfd);
    }
}