#pragma once

#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUF_MAX_LEN 1024
#define PORT 8080

typedef struct server_s server_t;
struct server_s{
    int sockfd;
    struct sockaddr_in server_addr;
};

server_t* server_init();
void server_destroy(server_t* server);
int server_process_data(server_t* server);

#endif