#include "stdio.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "stdbool.h"

#define MAXLINE 1000
typedef struct{

    int x;
    int y;

}User;

int main(void){

    int listenfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    
    char buff[MAXLINE];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1){
        fprintf(stderr, "Error with init socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(720);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        fprintf(stderr, "Error with bind socket");
        return -1;
    }

    if (listen(listenfd, 10) == -1){
        fprintf(stderr, "listen");
        return -1;
    }

    while (true){
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);

        printf("connection from %s, port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));
        User user = {.x = 15, .y = 13};

        if (send(connfd, &user, sizeof(user), 0)){
            printf("send is succes");
        }

        //close(connfd);
    }
}