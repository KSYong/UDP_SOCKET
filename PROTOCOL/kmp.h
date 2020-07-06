#pragma once

#ifndef _KMP_H_
#define _KMP_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define DATA_MAX_LEN 1024

typedef struct kmp_hd_s kmp_hd_t;
struct kmp_hd_s{
 	uint32_t seq_id;
	int data_len;
};

typedef struct kmp_s kmp_t;
struct kmp_s{
 	kmp_hd_t hd;
	char data[ DATA_MAX_LEN];
};

kmp_t* kmp_init();
void kmp_destroy( kmp_t* msg);
int kmp_get_data_len( kmp_t* msg);
int kmp_get_data_size();
char* kmp_get_data( kmp_t* msg);
int kmp_set_msg( kmp_t* msg, uint32_t seq_id, char* data);
void kmp_print_msg( kmp_t* msg);

#endif
