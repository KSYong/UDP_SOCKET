#include "server.h"

/**
 * @mainpage Project : UDP Socket programming
 * @section intro 소개 
 *      - UDP를 이용한 소켓 프로그래밍 예제 입니다
 * @section CreatInfo 작성 정보
 *      - 작성자 : 권승용
 *      - 작성일 : 2020/07/05
 * @subsection exec 실행 방법 및 인수 설명
 *      - 실행 방법\n
 *        서버       : SERVER/server
 *        클라이언트 : CLIENT/client
 */

/**
 * @fn int main()
 * @brief server를 실행하기 위한 메인 함수
 * @return int
 */
int main(){

    server_t* server = server_init();

    server_process_data(server);

    server_destroy(server);

    return 0;
}

/**
 * @fn server_t* server_init()
 * @brief server 객체를 생성하고 초기화하는 함수 
 * @return 생성된 server 객체
 */
server_t* server_init(){
    server_t* server = (server_t*)malloc( sizeof(server_t));

    if ((server->sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("socket creation failed!");
        free(server);
        return -1;
    }

    memset( &server->server_addr, 0, sizeof(server->server_addr));
	memset( &server->client_addr, 0, sizeof(server->client_addr));

    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = htons(PORT);

    if( bind(server->sockfd, (const struct sockaddr*)&server->server_addr, sizeof(server->server_addr)) < 0){
        perror("bind failed!!");
        free(server);
        return -1;
    }
	return server;
}

/**
 * @fn void server_destroy(server_t* server)
 * @brief server 객체를 삭제하기 위한 함수
 * @return void
 * @param server 삭제할 server 객체
 */
void server_destroy(server_t* server){
    if (close(server->sockfd) == -1){
        perror("close failed!");
    }
    free(server);
	printf("success to destroy server object\n");
}

/**
 * @fn int server_process_data(server_t* server)
 * @brief client에서 받은 데이터를 처리해서 응답하는 함수 
 * @return void 
 * @param server 데이터를 처리할 server 객체
 */
void server_process_data(server_t* server){
    if (server){
        ssize_t recv_byte;
        char read_buf[ DATA_MAX_LEN];
		kmp_t recv_msg;
        char* hello = "Hello from server";
		socklen_t len = sizeof(server->client_addr);
        recv_byte = recvfrom(server->sockfd, &recv_msg, sizeof( recv_msg), MSG_WAITALL, (struct sockaddr*)&server->client_addr, &len);
        if (recv_byte > 0){
			kmp_print_msg( &recv_msg);
			printf("Client to Server message sent!\n");
			printf("Client : %s\n", recv_msg.data);
        }
        else{
            perror("receiving data from client failed!\n");
        }
		
        if((sendto(server->sockfd, (const char*)hello, strlen(hello), 0, (const struct sockaddr*) &server->client_addr, sizeof(server->client_addr)) <= 0)){
            perror("server to client send failed!");
        }
        else{
            printf("Hello message sent from server to client.\n");
        }
    }
}
