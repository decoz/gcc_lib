/*
 * rid_io.c
 *
 *  Created on: 2009. 11. 30.
 *      Author: decoz
 */

#include "rid.h"
#include "rid_io.h"
#include <stdlib.h>
#include <stdio.h>
rid *create_rid_f(rid *fname){
	/*
	 * file �� �̸��� �̿��ؼ� ������ ������ �о
	 * �� ������ rid �� �����Ѵ�.
	 */
	FILE *fp = fopen(create_str(fname),"r");

	if(fp == NULL) return NULL;

	fseek(fp,0,SEEK_END);
	int size = ftell(fp);
	BYTE *buffer = (BYTE*)malloc(size);
	fseek(fp,0,SEEK_SET);
	fread(buffer,sizeof(char),size,fp);
	fclose(fp);

	rid *r = create_empty_rid();
	r->addr = buffer;
	r->size = size;


	return r;
}


