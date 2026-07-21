#include "protocol.h"
#include "server.h"
#include "handle_client.h"

#define DEFAULT_PORT 720
#define MAXUSERS 3

int main(void){

    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    pthread_mutex_t connMutex;
    socklen_t len;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1){
        perror("Error with init socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("Error while BINDING the socket");
        return -1;
    }

    if (listen(listenfd, MAXUSERS) == -1){
        perror("Error while trying to LISTEN");
    }

    UserData users[MAXUSERS];
    int userCount = 0;
    pthread_mutex_init(&connMutex, NULL);

    pthread_mutex_t sendMutexes[MAXUSERS];

    for (int i = 0; i < MAXUSERS; i++) {
        pthread_mutex_init(&sendMutexes[i], NULL);
    }

    while(true){
        len = sizeof(cliaddr);

        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);

        if (connfd == -1){
            fprintf(stderr, "ACK Error");
            continue;
        }

        ClientThreadArgs *args = malloc(sizeof(ClientThreadArgs));
        args->users = &users;
        args->userCount = &userCount;
        args->usersMutex = &connMutex;
        args->connfd = connfd;
        args->cliaddr = cliaddr;
        args->sendMutexes = sendMutexes;
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, args);
        pthread_detach(tid);
    }

    pthread_mutex_destroy(&connMutex);
    return 0;
}