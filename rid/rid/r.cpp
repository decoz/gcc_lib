/*
 * built-in rid 파서
 *
 */

#include "rid.h"
#include "stdio.h"
#include <string.h>

rid *rstr(char *str){

	BYTE *data = (BYTE*)str;
	int s = strlen(str);

	return rstr(create_rid_byte(data,s));

}

rid *rtab(rid *src){
/*
 *	tab 과 line feed 로 구성된 문법을 파싱
 */

	char *p = create_str(src),*np;
	char *ep = p + strlen(p);


	rid *stack[100]; 	// scope stack
	int tab[100];		// tab stack

	int sp = 0;			// stack pointer

	rid *rr = new rid();

	int li = 0, last_depth = 0;
	while(np < ep){

		np = strchr(p,'\n');
		if(np == NULL) np = ep;

		bool pre_tok = true;
		int depth = 0;
		BYTE *buff = new BYTE[np-p];
		int bp = 0;

		rid *lr = NULL, *nr = NULL;
		for(char *c=p;c<np;c++) { // line 스캔
			//printf("%c",*c);

			switch(*c){
			case '\t':
				if(pre_tok) {
					depth++;
					break;
				}
			case ' ':	// 스페이스로도 토큰을 분리하도록
				if(bp>0) {
					if(nr != NULL) {
						link_child(nr, create_rid_byte(buff,bp));
						nr = nr->cr;
					}
					else lr = nr = create_rid_byte(buff,bp);
					bp = 0;
				}
			break;
			default:
				pre_tok = false;
				buff[bp++] = *c;
			}

		}

		if(bp > 0)
			if(nr != NULL) {
				link_child(nr, create_rid_byte(buff,bp));
				nr = nr->cr;
			}
			else lr = nr =  create_rid_byte(buff,bp);

		int i=0;
		while( tab[i] < depth && i < sp)  i++;

		//printf("[%d,%d] :",i,depth);

		if(i>0) link_child(stack[i-1], lr);
		else link_child(rr,lr);


		stack[i] = lr;
		tab[i] = depth;
		sp = i+1;


		//printf("\n");
		p = np+1;
	}





	return rr->cr;

}


rid *rstr(rid *src){
/*
 * rid 문자열을 파싱 ( 미니멈 파서 )
 */



	BYTE *data = src->addr;
	int s = src->size;

	BYTE *tok;	// token start 위치
	int ts = 0;	// tok 크기

	rid *stack[100]; 	// scope stack
	int sp = 0;			// stack pointer

	rid *rr = new rid(), *cr = rr; //root, current, scope
	rid *nr;

	for(int i=0;i<s;i++){
		switch( (char)data[i] ){
		case ',':
			if(ts>0){
				nr = create_rid_byte(tok, ts);
				ts = 0;
				link_child(cr,nr);
			}
			cr = stack[sp-1];
			break;
		case '.':
			nr = create_rid_byte(tok, ts);
			ts = 0;
			link_child(cr,nr);
			cr = nr;
			break;

		case '(':
			nr = create_rid_byte(tok, ts);
			link_child(cr,nr);
			cr = nr;

			ts = 0;
			stack[sp++] = nr;
			break;

		case ')':
			if(ts>0){
				nr = create_rid_byte(tok, ts);
				ts = 0;
				link_child(cr,nr);
			}

			if(sp < 1) {
				printf("error_parsing %d", i);
			}
			cr = stack[sp-1];
			sp--;
			break;

		default:
			if(ts == 0) tok = data+i;
			ts++;
		}
	}

	if(ts>0) {
		nr = create_rid_byte(tok, ts);
		link_child(cr,nr);
	}

	return rr->cr;

}


