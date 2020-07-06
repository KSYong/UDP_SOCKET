#include "kmp.h"

kmp_t* kmp_init(){
 	kmp_t* msg = ( kmp_t*)malloc(sizeof( kmp_t));
	memset( msg->data, 0, sizeof( msg->data));
	return msg;
}

void kmp_destroy( kmp_t* msg){
 	if (msg){
 		memset( msg->data, 0, kmp_get_data_len( msg));
		free( msg);
	}
	else{
		perror("Message destroy error!");
	}
}

int kmp_get_data_len( kmp_t* msg){
 	if ( msg){
 		return strlen(msg->data);
	}
	else{
		perror("Get data length error!");
	}
}

int kmp_get_data_size(){
 	return sizeof( kmp_t) - sizeof( kmp_hd_t);
}

char* kmp_get_data( kmp_t* msg){
	if (msg){
		return msg->data;
	}
	else{
		perror("Get data error!");
	}
}

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

