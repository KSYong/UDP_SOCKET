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

typedef struct client_s client_t;
struct client_s{
    int sockfd;
    struct sockaddr_in server_addr;
};

client_t* client_init();
void client_destroy(client_t* client);
int client_process_data(client_t* client);

#endif