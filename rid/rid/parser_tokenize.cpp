/*
 * parser_tokenize.c
 *
 *  Created on: 2009. 9. 13.
 *      Author: decoz
 *
 *      로우 데이터의 파싱에 관련된 펑션 셋
 *
 *  target Data 를 token 베이스로 나누는 기능을한다.
 *  하나의 rid data를 여러개의 rid로 나누는 역할을 담당하며
 *  사이즈 단위부터 token 정규식까지 다양한 형태를  지원한다.
 *
 *
 *	정규식 파라미터
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
			 * 각 룰에 대해서 현 위치가 매칭인지 아닌지 검색
			 * 만일 매치될 경우 그것을 토큰 rid 로 생성해서 붙인다.
			 * 그 후 다음 위치까지 포인터 진행
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
	 * 재귀적으로 method 값과 pos값을 맞춰본 후에 매치인 경우 그 포인터를 진행시켜서
	 * 리턴시켜준다.
	 *
	 * 만일 매치가 아닌경우 NULL을 리턴한다. *
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

			if(*(s->addr) > *(e->addr)){ // 순서가 바뀐 경우
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
	//   trid 의 값이 method 인지 아닌지를 체크
	if(is_rid(trid,"-")) return 1;
	if(is_rid(trid,"or")) return 1;
	if(is_rid(trid,"and")) return 1;
	if(is_rid(trid,"+")) return 1;
	if(is_rid(trid,"*")) return 1;
	return 0;
}

