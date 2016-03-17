/*
 * rid_serialize.c
 *
 *  Created on: 2009. 11. 28.
 *      Author: decoz
 */
#include "stdlib.h"
#include "rid.h"
#include "rid_io.h"
#include <string.h>

int get_topology_r(rid *input,int *arr,int pos);
int restore_tpg_r(rid *trid,BYTE *start,int bit);

int get_size_info_r(rid *input,int *size,int pos);
int *restore_size_r(rid *input , int *cur);

BYTE *push_data_r(rid *input,BYTE *pos);
BYTE *resotre_data_r(rid *input, BYTE  *pos);


rid *serialize_struct(rid *input){
	/*
	 * rid 를 stream 형태의 BYTE 로 메모리 영역을
	 * 생성해 저장하고 이를 리턴한다.
	 */

	int i;

	// topology 생성
	int top[1000];
	int pos = get_topology_r(input,top,0);
	int n = pos/2;

	int top_size = pos/8;
	if(pos % 8 != 0) top_size++;

	// 길이 계산후 버퍼 생성
	int *size = (int*)malloc(n*4);
	pos = get_size_info_r(input,size,0);

	int data_size = 0;
	for(i=0;i<pos;i++)data_size += size[i];
	int buff_size = top_size+n*4+data_size;

	BYTE *buffer = (BYTE*) malloc(buff_size);

	// topology 입력
	BYTE *cur = buffer-1;
	for(i=0;i<n*2;i++){
		if(i%8 == 0) *(++cur)=0;
		else *cur *= 2;
		if( top[i] ) (*cur)++;

	}
	cur++;

	// size data 입력
	memcpy(cur,size,n*4);
	cur += n*4;

	// data 입력후 rid 출력
	push_data_r(input,cur);
	rid *result = create_empty_rid();
	result->size = buff_size;
	result->addr = buffer;

	return result;
}

rid *deserialize_struct(rid *input){

	BYTE *pos = input->addr;

	rid *root = create_empty_rid();
	int bcount = restore_tpg_r(root,pos,0);

	int tpg_size = bcount / 8;
	int node_count = bcount / 2;
	if(bcount % 8 != 0) tpg_size++;


	pos += tpg_size;
	restore_size_r(root,(int*)pos);

	pos += node_count * 4;
	resotre_data_r(root, pos);

	return root;
}



BYTE *push_data_r(rid *input,BYTE *pos){
	memcpy(pos,input->addr,input->size);
	pos += input->size;
	if(input->cr != NULL) pos = push_data_r(input->cr,pos);
	if(input->rr != NULL) pos = push_data_r(input->rr,pos);
	return pos;
}


int get_size_info_r(rid *input,int *size,int pos){
	size[pos++] = input->size;

	if(input->cr != NULL)
		pos = get_size_info_r(input->cr,size,pos);

	if(input->rr != NULL)
		pos = get_size_info_r(input->rr,size,pos);

	return pos;
}

int get_topology_r(rid *input,int *arr,int pos){
	if(input->cr != NULL) {
		arr[pos++] = 1;
		pos = get_topology_r(input->cr,arr,pos);
	}
	else arr[pos++] = 0;

	if(input->rr != NULL) {
		arr[pos++] = 1;
		pos = get_topology_r(input->rr,arr,pos);
	}
	else arr[pos++] = 0;

	return pos;
}


int restore_tpg_r(rid *trid,BYTE *start,int bit){

	BYTE b,marker;
	int bit_pos;

	bit_pos = bit % 8;
	b = *(start + bit / 8);
	marker = 128 >> bit_pos;
	bit++;

	if(b & marker) {
		trid->cr = create_empty_rid();
		bit = restore_tpg_r(trid->cr,start,bit);
	}

	bit_pos = bit % 8;
	b = *(start + bit / 8);
	marker = 128 >> bit_pos;
	bit++;

	if(b & marker){
		trid->rr = create_empty_rid();
		bit = restore_tpg_r(trid->rr,start,bit);
	}

	return bit;
}

int *restore_size_r(rid *input , int *cur){
	input->size = *cur;

	cur++;
	if(input->cr != NULL) cur = restore_size_r(input->cr,cur);
	if(input->rr != NULL) cur = restore_size_r(input->rr,cur);

	return cur;
}

BYTE *resotre_data_r(rid *input, BYTE  *pos){
	input->addr = pos;
	pos += input->size;
	if(input->cr != NULL) pos = resotre_data_r(input->cr,pos);
	if(input->rr != NULL) pos = resotre_data_r(input->rr,pos);

	return pos;
}
