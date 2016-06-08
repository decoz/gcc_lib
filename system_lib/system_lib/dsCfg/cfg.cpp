/*
 * cfg.cpp
 *
 *  Created on: 2016. 3. 14.
 *      Author: decoz
 */
#include <rid.h>
#include <rid_io.h>
#include <dsCfg/cfg.h>
#include <stdio.h>
#include <stddef.h>



cfg *cfg::it = NULL;

cfg::cfg() {
	cur = root = new rid();
}

cfg::~cfg() {
	// TODO Auto-generated destructor stub
}


void cfg::_set(char *path, char *value){
/*
 * 경로의 child 를 value 로  교체
 */

	rid *v_rid = rstr(value);
	rid *target = get_rid(cur, rstr(path));

}

char *cfg::_get(char *path){
/*
 *  value 값을 얻기위한 메소드
 *
 * 	자식노드가 있을 경우 : 자식노드값
 * 	경로의 값이 없거나 자식노드가 없으면 : ""
 */
	rid *p_rid = rstr(path);

	rid *target = get_rid(cur, p_rid);
	if(target == NULL || target->cr == NULL ) return "";


	return create_str(target->cr);
}

bool cfg::_is(char *path){
/*
 *  true/false 값을 얻기 위한 메소드
 *
 * 	자식노드가 없거나 자식노드가 true 이면 true
 * 	경로의 값이 없거나 자식노드가 false 이면 false
 */
	rid *p_rid = rstr(path);

	rid *target = get_rid(cur, p_rid);
	if(target == NULL) return false;
	else if(target->cr == NULL) return true;
	if(is_rid(target->cr, "false")) return false;
	else  return true;


}

void cfg::_print(){
	print_rid(root);
}

void cfg::_loadfile(char *fname, bool appand = false){

	printf("cfg load file\n");

	rid *buff_rid = create_rid_f(create_rid(fname));
	if(buff_rid == NULL){
		printf("error > can't find %s , loading cfg aborted\n",fname);
		return;
	}

	rid *new_cfg = rtab(buff_rid);

	if(appand) {
		put_rid(root, new_cfg);
	}
	else  root->cr = new_cfg;


	//print_rid(root);

}
