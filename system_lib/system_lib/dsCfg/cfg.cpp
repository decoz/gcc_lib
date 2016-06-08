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
 * ����� child �� value ��  ��ü
 */

	rid *v_rid = rstr(value);
	rid *target = get_rid(cur, rstr(path));

}

char *cfg::_get(char *path){
/*
 *  value ���� ������� �޼ҵ�
 *
 * 	�ڽĳ�尡 ���� ��� : �ڽĳ�尪
 * 	����� ���� ���ų� �ڽĳ�尡 ������ : ""
 */
	rid *p_rid = rstr(path);

	rid *target = get_rid(cur, p_rid);
	if(target == NULL || target->cr == NULL ) return "";


	return create_str(target->cr);
}

bool cfg::_is(char *path){
/*
 *  true/false ���� ��� ���� �޼ҵ�
 *
 * 	�ڽĳ�尡 ���ų� �ڽĳ�尡 true �̸� true
 * 	����� ���� ���ų� �ڽĳ�尡 false �̸� false
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
