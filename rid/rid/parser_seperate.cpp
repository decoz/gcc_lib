/*
 * parser_seperate.c
 *
 *  Created on: 2009. 9. 29.
 *      Author: decoz
 *
 *
 *
 *      seperator �� �Ϸ��� ��屺�� Ư�� �ɺ��� �̿��ؼ� �����ִ� ������ �Ѵ�.
 *      recursive �� ������ ���� �̰��� ������ �������� ���ؼ� ��� �����Ѵ�.
 *
 *      ��:
 *
 *      	a, *, b, c, d, *, e, f
 *
 *      	> seperate.method.*
 *
 *      	->
 *      		/
 *      			a
 *      		/
 *      			b
 *      			c
 *      			d
 *      		/
 *      			e
 *      			f
 *
 *			������:
 *
 *			���� seperator������ �ϴ� ��� �׿� child �� �ִ� ���  �� ���ϵ��
 *			�����ȴ�.
 *
 */


#include "stdlib.h"
#include "parser.h"


rid *seperate_r(rid *parent,rid *sep,rid *as);

rid *seperate(rid *target,rid *sep){

	rid *dummy = create_rid("");
	dummy->cr = target;

	rid *rid_method = get_child_d(sep,"method");
	rid *as = get_child_d(sep,"as");

	if(as!=NULL) {
		as = as->cr;
	}

	if(is_rid(rid_method,"method"))
		seperate_r(dummy,rid_method->cr,as);

	return dummy->cr;

}


rid *seperate_r(rid *parent,rid *sep,rid *as){

	if(parent == NULL) return NULL;
	rid *crid = parent->cr;

	rid *r_first = create_rid("/");
	if(as != NULL )copy_rid_value(as,r_first);

	rid *r_pos = r_first;

	rid *before = NULL;
	while(crid != NULL ){

		if(cmp_rid(crid,sep)){
			//printf("////");

			r_pos->rr = create_rid("/");
			if(as != NULL)copy_rid_value(as,r_pos->rr);

			r_pos = r_pos->rr;

			if(before != NULL) before->rr = NULL;
			before = NULL;

			crid = crid->rr;

		}
		else {
			//printf("["); print_single_rid(crid);printf("]");
			if(before==NULL) link_child(r_pos,crid);
			if(crid->cr != NULL)seperate_r(crid,sep,as);
			before = crid;
			crid = crid->rr;
		}

	}

	parent->cr = r_first;

	return parent;

}

