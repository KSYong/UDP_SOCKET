#include "client.h"

// Driver code 
int main() { 

    client_t* client = client_init();

    client_process_data(client);

    client_destroy(client);

    return 0;
} 

client_t* client_init(){
    client_t* client = (client_t*)malloc(sizeof(client_t));
    
    if ((client->sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("socket creation failed!");
        free(client);
        return -1;
    }

    memset(&client->server_addr, 0, sizeof(client->server_addr));

    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(PORT);
    client->server_addr.sin_addr.s_addr = INADDR_ANY;
}

void client_destroy(client_t* client){
    if (close(client->sockfd) == -1){
        perror("close failed!");
    }
    free(client);
}

int client_process_data(client_t* client){
    char buffer[BUF_MAX_LEN];
    char *hello = "Hello from client to server";
    if((sendto(client->sockfd, (const char*)hello, strlen(hello), 0, (const struct sockaddr*) &(client->server_addr), sizeof(client->server_addr) <= 0))){
        perror("server to client send failed!");
    }
    else{
        printf("Hello message sent from client to server.\n");
    }

    ssize_t recv_byte;
    recv_byte = recvfrom(client->sockfd, (char*) buffer, BUF_MAX_LEN, MSG_WAITALL, (struct sockaddr*)&(client->server_addr), sizeof(client->server_addr));
    if (recv_byte > 0){
        buffer[recv_byte] = '\0';
        printf("Server : %s\n", buffer);
    }
    else{
        perror("receiving data from server failed!\n");
    }
}