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

/// @struct server_t
/// @brief client의 메시지 요청에 대한 응답을 처리하기 위한 구조체
typedef struct server_s server_t;
struct server_s{
    /// server의 socket file descriptor
    int sockfd;
    /// server의 socket address
    struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
};

server_t* server_init();
void server_destroy(server_t* server);
void server_process_data(server_t* server);

#endif
