#include "protocol.h"
#include "server.h"

int main(void){

    int listenfd, connfd;
    
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;

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

    if (listen(listenfd, MAXUSERS) == -1){
        fprintf(stderr, "Error while trying to LISTEN socket");
        return -1;
    }

    UserData user;
    UserData *users = malloc(MAXUSERS * sizeof(UserData));
    int userCount = 0;
    int conn = 0;
    
    while (true){

        len = sizeof(cliaddr);
        connfd = accept(listenfd,  (struct sockaddr *)&cliaddr, &len);
        
        if (connfd == -1){
            fprintf(stderr, "ACK Error");
            continue;
        }
       
        user.port = ntohs(cliaddr.sin_port);
        strcmp(user.ip, inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, user.ip, sizeof(user.ip)));

        printf("connection from %s, port %d\n", user.ip, user.port);
        
        if ((conn = checkUser(&users, &user)) != -1){
            
            if (recv(connfd, &user, sizeof(user), 0) > 0){
            
                printf("Server got data Succesfully: UserData->x = %d, UserData->y = %d\n", user.x, user.y);
                inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, user.ip, sizeof(user.ip));
             
                updateUser(&users, &user, &conn);
            }
            close(connfd); 
        }else if (userCount < MAXUSERS){
    
            printf("hello %d\n", userCount);
            addUser(&users, &user, &userCount);
    
        }else{
        
            printf("Reached the limit of users\n"); 
            close(connfd); 
        }

        printf("==============================USERS==========================\n");
        for (int i = 0; i < userCount; i++){
            printf("||User ip: %s   User port: %d                    ||\n", users[i].ip, users[i].port);
        }
        printf("=============================================================\n\n");
        
    }
    close(connfd);
    free(users);
}