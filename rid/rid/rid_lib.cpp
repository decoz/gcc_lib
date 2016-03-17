/*
 * rid_lib.c
 *
 *  Created on: 2009. 9. 4.
 *      Author: decoz
 *
 *      rid ���ݿ� ���� ���Ǵ� ���� ��Ǽ�
 */

//BYTE data ������ ���Կ��θ� �˻��ϴ� ��ƾ, ������ �� �����ġ���� ������ -1�� �����Ѵ�.
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

