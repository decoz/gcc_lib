/*
 * dsSeq.cpp
 *
 *  Created on: 2016. 2. 19.
 *      Author: decoz
 */

#include "dsSeq.h"
dsSeq *dsSeq::it = NULL;



dsSeq::dsSeq() {

	current = 0;
	for(int i=0;i<10;i++)
		postfix[i] = prefix[i] = NULL;

	digit_cnt  = 2;
}

dsSeq::~dsSeq() {

}

char *digit2str(int n, int dcnt ){
/* n 자리의 정수로 문자열을 만들어 리턴한다. (001, 002 등) */

	char *buff = new char[100];

	int cmp = 10;
	int zero_cnt = 0;
	for(int i=0;i<dcnt;i++){
		if(n < cmp) {
			zero_cnt = dcnt - i - 1;
			break;
		}
		cmp *= 10;
	}

	for(int i=0;i<zero_cnt;i++) buff[i] = '0';
	sprintf( buff + zero_cnt,  "%d", n);
	return buff;
}

void 	dsSeq::_setPrefix(int n, char *str, bool reset){

	if(n < 10){
		char *n_str = new char[strlen(str)];
		strcpy(n_str,str);
		prefix[n] = n_str;
	}

	if(reset)  current = 0;
}

void 	dsSeq::_setPostfix(int n, char *str, bool reset){

	if(n < 10){
		char *n_str = new char[strlen(str)];
		strcpy(n_str,str);
		postfix[n] = n_str;
	}

	if(reset)  current = 0;
}

char*	dsSeq::_next(){
	char *buff = new char[100];
	int c = 0;

	for(int i=0;i<10;i++)
		if(prefix[i] != NULL) {
			strcpy(buff + c, prefix[i]);
			c += strlen(prefix[i]);
		}

	char *digit = digit2str(current++, digit_cnt);
	sprintf(buff + c,"%s", digit);
	c += strlen(digit);

	for(int i=0;i<10;i++)
		if(postfix[i] != NULL) {
			strcpy(buff + c, postfix[i]);
			c += strlen(postfix[i]);
		}


	return buff;
}


void dsSeq::_setDigitCount(int cnt){

	digit_cnt = cnt;

}
