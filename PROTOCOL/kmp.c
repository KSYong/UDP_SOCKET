#include "kmp.h"

/**
 * @fn kmp_* kmp_init()
 * @brief 프로토콜 메시지 객체를 생성하고 초기화하기 위한 함수
 * @return 프로토콜 메시지 객체
 */
kmp_t* kmp_init(){
 	kmp_t* msg = ( kmp_t*)malloc(sizeof( kmp_t));
	memset( msg->data, 0, sizeof( msg->data));
	return msg;
}

/**
 * @fn void kmp_destroy(kmp_t* msg)
 * @brief 프로토콜 메시지 객체를 삭제하기 위한 함수 
 * @return void
 * @param msg 삭제할 프로토콜 객체
 */
void kmp_destroy( kmp_t* msg){
 	if (msg){
 		memset( msg->data, 0, kmp_get_data_len( msg));
		free( msg);
	}
	else{
		perror("Message destroy error!");
	}
}

/**
 * @fn int kmp_get_data_len( kmp_t* msg)
 * @brief 프로토콜 메시지 바디의 데이터 길이를 구하는 함수
 * @return 메시지 바디의 데이터 길이
 * @param msg 데이터 길이를 구할 메시지 객체 
 */
int kmp_get_data_len( kmp_t* msg){
 	if ( msg){
 		return strlen(msg->data);
	}
	else{
		perror("Get data length error!");
	}
}

/**
 * @fn int kmp_get_data_size()
 * @brief 프로토콜 메시지 바디의 데이터 크기를 구하는 함수
 * @return 메시지 바디의 데이터 크기 
 */
int kmp_get_data_size(){
 	return sizeof( kmp_t) - sizeof( kmp_hd_t);
}

/**
 * @fn char* kmp_get_data( kmp_t* msg)
 * @brief 프로토콜 메시지 바디의 데이터를 구하는 함수
 * @return 메시지 바디의 데이터(문자열)
 * @param msg 데이터를 구할 메시지 객체
 */
char* kmp_get_data( kmp_t* msg){
	if (msg){
		return msg->data;
	}
	else{
		perror("Get data error!");
	}
}

/**
 * @fn int kmp_set_msg( kmp_t* msg, uint32_t seq_id, char* data)
 * @brief 프로토콜 메시지의 헤더와 바디를 지정하는 함수
 * @return 성공 여부( 1: success, -1 : fail)
 * @param msg 지정하려 하는 메시지 객체
 * @param seq_id 지정하려 하는 메시지 헤더의 sequence identifier
 * @param data 지정하려 하는 메시지 바디 데이터
 */
int kmp_set_msg( kmp_t* msg, uint32_t seq_id, char* data){
	if( data != NULL){
		int len = strlen( data);
		memset( msg->data, 0, DATA_MAX_LEN);
		data[ len] = '\0';
		memcpy( msg->data, data, strlen(data));
		msg->hd.seq_id = seq_id;
		msg->hd.data_len = len;
		return 1;
	}
	return -1;
}

/**
 * @fn void kmp_print_msg( kmp_t* msg)
 * @brief 프로토콜 메시지 전체를 출력하는 함수
 * @return void
 * @param msg 출력할 메시지 객체
 */
void kmp_print_msg( kmp_t *msg){
	if (msg == NULL){
		perror("message NULL!");
		return;
	}

	printf("********msg header\n");
	printf("* msg seq id : %d\n", msg->hd.seq_id);
	printf("* msg data len : %d\n", msg->hd.data_len);

	printf("********msg body\n");
	printf("* msg data : %s\n\n", msg->data);
}

