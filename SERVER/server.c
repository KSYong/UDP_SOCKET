#include "server.h"

int main(){

    server_t* server = server_init();

    server_process_data(server);

    server_destroy(server);

    return 0;
}

server_t* server_init(){
    server_t* server = (server_t*)malloc( sizeof(server_t));

    if ((server->sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("socket creation failed!");
        free(server);
        return -1;
    }

    memset( &server->server_addr, 0, sizeof(struct sockaddr));

    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = htons(PORT);

    if( bind(server->sockfd, (const struct sockaddr*)&server->server_addr, sizeof(server->server_addr)) < 0){
        perror("bind failed!!");
        free(server);
        return -1;
    }
}

void server_destroy(server_t* server){
    if (close(server->sockfd) == -1){
        perror("close failed!");
    }
    free(server);
}

int server_process_data(server_t* server){
    if (server){
        ssize_t recv_byte;
        struct sockaddr_in client_addr;
        char buffer[BUF_MAX_LEN];
        char* hello = "Hello from server";
        recv_byte = recvfrom(server->sockfd, (char*) buffer, BUF_MAX_LEN, MSG_WAITALL, (struct sockaddr*)&client_addr, sizeof(client_addr));
        if (recv_byte > 0){
            buffer[recv_byte] = '\0';
            printf("Client : %s\n", buffer);
        }
        else{
            perror("receiving data from client failed!\n");
        }
        if((sendto(server->sockfd, (const char*)hello, strlen(hello), 0, (const struct sockaddr*) &client_addr, sizeof(client_addr) <= 0))){
            perror("server to client send failed!");
        }
        else{
            printf("Hello message sent from server to client.\n");
        }
    }
}