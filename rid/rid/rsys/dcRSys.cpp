/*
 * dcRSys.cpp
 *
 *  Created on: 2016. 3. 30.
 *      Author: decoz
 */

#include "dcRSys.h"
#include "string.h"
#include <stdio.h>

dcRSys::dcRSys() {
	// TODO Auto-generated constructor stub
	path[0] = cur = root = create_rid("");
	pcnt = 1;

	prompt[0] = '.';
	prompt[1] = 0;
}

dcRSys::~dcRSys() {
	// TODO Auto-generated destructor stub
}



void *cout_rid_r(rid *r, int depth){

	for(int i=0;i<depth * 5;i++) putc(' ',stdout);
	for(int i=0;i<r->size;i++) putc((char) r->addr[i],stdout);
	putc('\n', stdout);

	if(r->cr != NULL) cout_rid_r(r->cr, depth+1);
	if(r->rr != NULL) cout_rid_r(r->rr, depth);

}

void *cout_rid(rid *r){

	cout_rid_r(r,0);

}

void dcRSys::cur_path(){

	for(int pi=0;pi<pcnt;pi++) {
		if(pi>0) putc('.',stdout);
		for(int i=0;i<path[pi]->size;i++)
			putc((char) path[pi]->addr[i],stdout);
	}
	putc('\n',stdout);

}

rid *dcRSys::go(rid *r, rid *rpath){
	/*
	 * 현재의 위치를 r에서 path로 옮김
	 * 시작이 .으로 시작하면 root
	 */

	rid *n_path = rpath;
	rid *n_r = r;

	int bck_pcnt = pcnt;
	rid **bck_path = NULL;

	if(rpath->size == 0){
		bck_path = new rid*[pcnt]; // 현재 패스를 백업
		memcpy(bck_path, path, sizeof(rid*) * pcnt);

		pcnt = 0;
		n_r = root;
		n_path = rpath->cr;
	}

	while(n_path != NULL){

		n_r = get_child(n_r, n_path);

		if(n_r == NULL) {		// 실패
			pcnt = bck_pcnt;
			if(bck_path != NULL) memcpy(path,bck_path, sizeof(rid*) * pcnt);

			cur = path[pcnt-1];
			return cur;
		}
		path[pcnt++] = n_r; 	// 성공
		n_path = n_path->cr;
	}

	cur = n_r;

	/*prompt update*/
	strncpy(prompt,(char*) cur->addr, cur->size);
	prompt[cur->size] = '.';
	prompt[cur->size + 1] = 0;

	return cur;


}

rid *dcRSys::cut(rid *r, rid *rpath) {

	rid *pr = get_rid_p(r, rpath);

	rid *term = rpath;
	while(term->cr != NULL) term = term->cr;

	if(pr != NULL){
		unlink_child(pr, term);
	}

	return term;
}


rid *dcRSys::cmd(rid *r) {

	if(is_rid(r,"put")){
		// put rid data
		if(r->cr != NULL) put_rid(cur,r->cr);
		else printf("need more parameter");

		return cur;
	}

	if(is_rid(r,"ls")) {
		cout_rid(cur);
		return cur;
	}

	if(is_rid(r,"go")){
		if(r->cr != NULL) cur = go(cur, r->cr);
		else cur = go(cur, last);
		cur_path();
		return cur;
	}

	if(is_rid(r,"path")){
		cur_path();
		return cur;
	}


	if(is_rid(r,"cut")){
		if(r->cr != NULL) cur = cut(cur, r->cr);
	}




	return cur;
	//print_rid(cur);

}


void dcRSys::interprete(const char *input){

	char *buff = new char[strlen(input)];
	strcpy(buff,input);

	char *ptr;

	ptr = strtok(buff, " ");

	if(!ptr) return;


	rid *crid = create_rid(ptr);

	while(ptr != NULL){
		ptr = strtok(NULL, " ");
		if(ptr != NULL) link_child(crid, rstr(ptr));

	}

	last = cmd(crid);



}
