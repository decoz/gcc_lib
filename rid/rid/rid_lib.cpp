/*
 * rid_lib.c
 *
 *  Created on: 2009. 9. 4.
 *      Author: decoz
 *
 *      rid 전반에 걸쳐 사용되는 기초 펑션셋
 */

//BYTE data 사이의 포함여부를 검색하는 루틴, 있으면 그 상대위치값을 없으면 -1을 리턴한다.
#include "rid_lib.h"
int contains(BYTE *source,int ssize,BYTE *target,int tsize){
	int spos = 0;
	int tpos = 0;


	int match = 0;
	while(!match && spos < ssize){
		if(source[spos] == target[tpos]){
			spos++;
			tpos++;
			if(tpos == tsize) match = 1;
		}
		else if(tpos==0) spos++;
		else tpos = 0;
	}

	if(match) return spos-tpos;
	else return -1;

}

