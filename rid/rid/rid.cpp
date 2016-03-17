/*
 * rid.c
 *
 *  Created on: 2009. 9. 2.
 *      Author: decoz
 */
#include "rid.h"
#include "rid_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

rid *create_rid_byte(BYTE *addr,int size){

	rid *t = (rid*) malloc(sizeof(rid));
	t->cr = NULL;
	t->lr = NULL;
	t->rr = NULL;

	t->type = T_NORMAL;
	t->size = size;
	t->addr = (BYTE*) malloc(size);

	memcpy(t->addr,addr,size);
	return t;

}
rid *create_irid(rid *trid){

	rid *t = (rid*) malloc(sizeof(rid));
	t->cr = NULL;
	t->lr = NULL;
	t->rr = NULL;

	t->type = T_INDIRECT;
	t->size = PSIZE;
	t->addr = (BYTE*)trid;

	return  t;

}

rid *create_rid(char *data){

	rid *t = (rid*) malloc(sizeof(rid));
	t->cr = NULL;
	t->lr = NULL;
	t->rr = NULL;

	t->type = T_NORMAL;
	t->size = strlen(data);
	t->addr = (BYTE*) malloc(t->size);

	memcpy(t->addr,data,t->size);
	return t;
}

rid *create_empty_rid(){
		rid *t = (rid*) malloc(sizeof(rid));
		t->cr = NULL;
		t->lr = NULL;
		t->rr = NULL;

		t->type = T_NORMAL;
		t->size = 0;
		t->addr = NULL;
}

char *create_str(rid *input){
	BYTE *str = (BYTE*) malloc(input->size + 1);
	memcpy(str,input->addr,input->size);
	str[input->size] = 0;
	return (char*) str;
}


rid *struct_rid_c(char *data,rid *rule)
{ return struct_rid(create_rid(data),rule); }


rid *struct_rid(rid *src,rid *rule){

	return parse(src,rule);

}


// source 의 Data 를 타겟에 복사한다.

void *copy_rid_value(rid *source,rid *target){
	free(target->addr);
	target->addr = (BYTE*) malloc(source->size);
	target->size = source->size;

	memcpy(target->addr,source->addr,source->size);
}

rid *copy_rid_struct_r(rid *source){
	rid *trid = create_rid_byte(source->addr,source->size );
	trid->type = source->type;
	if(source->cr != NULL) trid->cr = copy_rid_struct_r(source->cr);
	if(source->rr != NULL) trid->cr = copy_rid_struct_r(source->rr);

	return trid;
}

void remove_rid(rid *trid){
	free(trid->addr);
	free(trid);
}

rid *link_child(rid *parent,rid *child){
	if(parent == NULL)return NULL;
	if(parent->cr == NULL){
		parent->cr = child;
	}
	else{
		rid *last = parent->cr;

		/* find last */
		while(last->rr!=NULL){
			last = last->rr;
		}

		last->rr = child;
	}
	return child;
}

rid *link_brother(rid *elder, rid *younger){
	/*
	 *	  형제를 추가한다. elder 의 가장 최종 단말에 추가하게 된다.
	 *	  만일 elder가 NULL 인경우 younger 가 elder 가 된다.
	 *	  리턴은 둘이 NULL 인 경우 NULL 이 되며 정상은 elder 가 리턴된다.
	 */
	rid *t_elder = elder;
	if(t_elder != NULL){
		while(t_elder->rr != NULL)t_elder = t_elder->rr;
		t_elder->rr = younger;
		return elder;
	}
	else return younger;


}

void unlink_child(rid *parent,rid *child){
	rid *t,*next;
	if(parent->cr == child){
		t = parent->cr;
		parent->cr = t->cr;
		remove_rid(t);
	}
	else {
		t = parent->cr;
		while(t->rr != NULL){
			if(t->rr == child){
				next = t->rr->rr;
				remove_rid(t->rr);
				t->rr = next;

				break;
			}
			else t = t->rr;
		}
	}
}

void unlink_child_n(rid *parent,int child_n){
	int i;
	rid *t,*next;
	if(child_n == 0){
		t = parent->cr;
		if(t != NULL){
			parent->cr = t->rr;
			remove_rid(t);
		}
	}
	else{
		t = parent->cr;
		for(i=0;i<child_n-1;i++)
			if(t != NULL) t = t->rr;
			else break;

		if(t != NULL && t->rr != NULL){
			next = t->rr->rr;
			remove_rid(t->rr);
			t->rr = next;
		}
	}
}


void unlink_child_all(rid *parent){
	rid *t,*next;
	t = parent->cr;
	parent->cr = NULL;

	while(t != NULL){
		next = t->rr;
		remove_rid(t);
		t = next;
	}


}





rid *get_child_n(rid *parent, int n){
	int i;
	if(parent != NULL){
		return get_rid_n(parent->cr,n);
	}
	else return NULL;
}

rid *get_rid_i(rid *irid){
	//irid 로부터 그 타겟 rid 를 얻어준다.
	if(irid == NULL) return NULL;
	if(irid->type == T_INDIRECT){
		rid *t = (rid*)irid->addr;
		//printf("get_rid_i:");print_single_rid(t);printf("\n");
		return t;
	}
	else return NULL;
}


rid *get_rid_n(rid *irid , int n){
	/*
	 * n번째 rid를 찾는다. (src 의 형제중에)
	 * 시작은 0 부터 시작한다.
	 *
	 */
	int i;
	rid *t = irid;
	if(t==NULL || n < 0) return NULL;
	for(i=0;i<n;i++){
		if(t->rr != NULL) t = t->rr;
		else return NULL;
	}

	return t;
}

rid *get_rid_by_path(rid *src,BYTE *path,int pc){
	/*
	 * path 문자열의 .1.1  이나  .1.3 등의 경로를 이용해
	 * 경로를  찾는다.
	 *
	 */

	char start_symbol = '$';
	char sep = '.';

	if(*path != start_symbol) return NULL;
	rid *cur = src;

	int i;
	int n = -1;
	for(i=1;i<pc;i++){
		if( path[i] == sep){

			cur = get_rid_n(cur,n);

			/*
			printf("get_rid_by_path:(%d)",n);
			print_single_rid(cur); printf("\n");
			*/
			if(cur == NULL ) return NULL;
			else cur = cur->cr;

			n = -1;
		}
		else if( path[i] >= '0' && path[i] <= '9'){
			if(n < 0) n = path[i] - '0';
			else n = n * 10 + path[i] - '0';
		}
	}
	/*
	 * printf(" (%d)>>",n);
	 * print_single_rid(cur);
	 * printf("\n");
	 */
	cur = get_rid_n(cur,n);

	if(cur == NULL) return NULL;
	else return cur;

}



rid *get_child_d(rid *parent, char *data){

	rid *t = parent->cr;
	while(t!=NULL){
		if(is_rid(t,data)) return t;
		t = t->rr;
	}

	return NULL;
}

rid *get_gchild(rid *parent, char *data){

	rid *c = get_child_d(parent,data);
	if(c != NULL) return c->cr;
	else return NULL;

}



int get_child_count(rid *parent){
	int count = 0;
	if(parent->cr != NULL){
		count = 1;
		rid *last = parent->cr;

		/* find last */
		while(last->rr!=NULL){
			last = last->rr;
			count++;
		}
	}
	return count;

}


rid *find_child_contains(rid *root,char *subdata){
	return find_child_contains_r(root,subdata);
}


// 타겟 스트링을 포함한 최초의 rid를 depth first 로 찾아 리턴한다.
rid *find_child_contains_r(rid *parent, char *subdata){

		rid *rrid = NULL;

		if( contains(parent->addr,parent->size, (BYTE*) subdata,strlen(subdata)) != -1 ) return parent;
		else {
			if(parent->cr != NULL) rrid = find_child_contains_r(parent->cr,subdata);
			if(rrid != NULL) return rrid;
			if(parent->rr != NULL) rrid = find_child_contains_r(parent->rr,subdata);
			if(rrid != NULL) return rrid;
		}
		return NULL;
}



/*
rid *find_path(rid *root,char *subdata);
*/

void print_rid(rid *root){
	int depth = 0;
	print_rid_r(root,depth);


}

void print_rid_r(rid *trid,int depth){

	int i;
	for(i=0;i<depth;i++) printf("\t");
	print_single_rid(trid);
	printf("\n");

	if(trid != NULL){
		if(trid->cr != NULL) print_rid_r(trid->cr,depth + 1);
		if(trid->rr != NULL) print_rid_r(trid->rr,depth);
	}
}


void print_single_rid(rid *trid){
	int i;


	if(trid != NULL){
		int type = trid->type;

		if(type > 100) {
			type -= 100;
			printf("!");
		}

		while(type == T_INDIRECT){
			trid = (rid*)(trid->addr);
			printf("*");
			type = trid->type;
		}

		if(trid->size == 0) printf("\\");
		for(i=0;i<trid->size;i++){
			BYTE c = trid->addr[i];
			if( (c >='a' && c<='z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
				|| c == ',' || c == '/' || c == '.' || c== '$'

			)
				printf(".%c",c);
			else
				printf("%1x%1x ",c/16,c%16);
		}
	}
	else printf("\\!");
}


/*
 * data 의 값과 rid 의 주소값을 비교하여 같은면 1 아니면 0을 리턴한다.
 * 두 데이터의 크기도 정확하게 매칭되어야한다.
 */
int is_rid(rid *trid,char *data){
	int i;
	if(trid->size != strlen(data)) return 0;
	for(i=0;i<trid->size;i++){
		if(*(trid->addr + i) != data[i]) return 0;
	}
	return 1;
}

int cmp_rid(rid *trid, rid *srid){
	int i;

	if(trid->size != srid->size) return 0;
	for(i=0;i<trid->size;i++){
		if(*(trid->addr + i) !=  *(srid->addr + i)) return 0;
	}
	return 1;

}


