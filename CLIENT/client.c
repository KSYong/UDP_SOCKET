#include "client.h"

/**
 * @fn int main()
 * @brief client를 실행하기 위한 메인 함수
 * @return int
 */
int main() { 

    client_t* client = client_init();

    client_process_data(client);

    client_destroy(client);

    return 0;
} 

/**
 * @fn client_t* client_init()
 * @brief client 객체를 생성하고 초기화하는 함수
 * @return 생성된 client 객체
 */
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

	return client;
}

/**
 * @fn void client_destroy(client_t* client)
 * @brief client 객체를 삭제하기 위한 함수
 * @return void
 * @param client 삭제할 client 객체
 */
void client_destroy(client_t* client){
    if (close(client->sockfd) == -1){
        perror("close failed!");
    }
    free(client);
}

/**
 * @fn void client_process_data(client_t* client)
 * @brief server로 메시지 요청을 보내서 응답을 받는 함수
 * @return void
 * @param client 메시지 요청을 하기 위한 client 객체
 */
void client_process_data(client_t* client){
    char buffer[BUF_MAX_LEN];
    char *hello = "Hello from client to server";
    if((sendto(client->sockfd, (const char*)hello, strlen(hello), 0, (const struct sockaddr*) &(client->server_addr), sizeof(client->server_addr)) <= 0)){
        perror("client to server send failed!");
    }
    else{
        printf("Hello message sent from client to server.\n");
    }

    ssize_t recv_byte;
	socklen_t len = sizeof(client->server_addr);
    recv_byte = recvfrom(client->sockfd, (char*) buffer, BUF_MAX_LEN, MSG_WAITALL, (struct sockaddr*)&client->server_addr, &len);
    if (recv_byte > 0){
        buffer[recv_byte] = '\0';
        printf("Server : %s\n", buffer);
    }
    else{
        perror("receiving data from server failed!\n");
    }
}
