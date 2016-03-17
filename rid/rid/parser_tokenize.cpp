/*
 * parser_tokenize.c
 *
 *  Created on: 2009. 9. 13.
 *      Author: decoz
 *
 *      �ο� �������� �Ľ̿� ���õ� ��� ��
 *
 *  target Data �� token ���̽��� ������ ������Ѵ�.
 *  �ϳ��� rid data�� �������� rid�� ������ ������ ����ϸ�
 *  ������ �������� token ���Խı��� �پ��� ���¸�  �����Ѵ�.
 *
 *
 *	���Խ� �Ķ����
 *
 *	[0-9] : 	-(0,9)
 *	[0-9]*:		*.-(0,9)
 *	[0-9]+:		+.-(0,9)
 *	[a-zA-z]:	or(-(a,z),-(A,Z))
 *
 *
 *	ver 1: [AS.$name,]method.char.[char]
 *	ver 2: [AS.$name,]method.and,or,-
 *	ver 3: [AS.$name,]method.*,and,or,-
 *
 */
#include <stdlib.h>
#include "parser.h"


rid *tokenize(rid *target,rid *token){

	BYTE *ptr = target->addr;
	BYTE *end = ptr + target->size;
	BYTE *pos = ptr;

	rid *method,*result;
	result = create_rid("result");

	while(pos < end){
		rid *rule = token->cr;

		BYTE *rpos = NULL;

		while(rule != NULL && rpos == NULL){
			/*
			 * �� �꿡 ���ؼ� �� ��ġ�� ��Ī���� �ƴ��� �˻�
			 * ���� ��ġ�� ��� �װ��� ��ū rid �� �����ؼ� ���δ�.
			 * �� �� ���� ��ġ���� ������ ����
			 */
			method = get_gchild(rule,"method");
			if(method != NULL){
				rpos = match_r(method,pos,end);
			}

			rule = rule->rr;
		}

		if(rpos == NULL) {
			pos++;
		}
		else {
			link_child(result,create_rid_byte(pos,rpos-pos));
			pos = rpos;
		}
	}
	return result->cr;
}



BYTE *match_r(rid *method,BYTE *pos,BYTE *end){
	/*
	 * ��������� method ���� pos���� ���纻 �Ŀ� ��ġ�� ��� �� �����͸� ������Ѽ�
	 * ���Ͻ����ش�.
	 *
	 * ���� ��ġ�� �ƴѰ�� NULL�� �����Ѵ�. *
	 */

	//print_single_rid(method);

	rid *t;
	if(!is_token_method(method)){
		t = method;
		if(t!=NULL && pos + t->size <= end){
			int match = 1;
			int i;
			for(i=0;i<t->size;i++){
				if(*(t->addr + i) != *(pos+i)) match = 0;
			}

			if(match) return pos + t->size;
			else return NULL;
		}
		else return NULL;
	}
	else{
		if(is_rid(method,"-")){
			rid *s,*e;

			s = method->cr;
			if(s != NULL) e = s->rr;

			if(*(s->addr) > *(e->addr)){ // ������ �ٲ� ���
				BYTE *temp;
				temp = s->addr;
				s->addr = e->addr;
				e->addr = temp;
			}
			if(t!=NULL && e!=NULL)
				if(*pos >= *(s->addr) && *pos <= *(e->addr) )
					return pos+1;
				else return NULL;
			else return NULL;
		}


		if(is_rid(method,"or")){
			rid *c = method->cr;
			BYTE *rpos = NULL;
			while(c!=NULL && rpos == NULL){
				rpos = match_r(c,pos,end);
				c = c->rr;
			}
			return rpos;
		}

		if(is_rid(method,"and")){
			rid *c = method->cr;
			BYTE *rpos = pos;
			while(c!=NULL && rpos != NULL){
				rpos = match_r(c,pos,end);
				pos = rpos;
				c = c->rr;
			}
			return rpos;
		}

		if(is_rid(method,"+")){

			BYTE *rpos = pos;
			BYTE *tpos = NULL;
			while(rpos != NULL){
				rid *c = method->cr;
				while(c!=NULL && rpos != NULL){
					rpos = match_r(c,pos,end);
					pos = rpos;
					c = c->rr;
				}

				if(rpos != NULL) tpos = rpos;
			}

			return tpos;
		}

	}
	return NULL;
}



int is_token_method(rid *trid){
	//   trid �� ���� method ���� �ƴ����� üũ
	if(is_rid(trid,"-")) return 1;
	if(is_rid(trid,"or")) return 1;
	if(is_rid(trid,"and")) return 1;
	if(is_rid(trid,"+")) return 1;
	if(is_rid(trid,"*")) return 1;
	return 0;
}

