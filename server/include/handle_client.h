#ifndef HANDLE_CLIENT_H
#define HANDLE_CLIENT_H

#include "server.h"
#include "stdio.h"
#include "string.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "protocol.h"

void* handle_client(void *arg);

#endif