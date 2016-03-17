/*
 * parser_bind.c
 *
 *  Created on: 2009. 9. 18.
 *      Author: decoz
 *
 *
 *
 */

#include "stdlib.h"
#include "parser.h"

rid *box(rid *target,rid *bind){

	rid *dummy = create_rid("");
	rid *cur = target;
	rid *c_p = dummy;

	rid *stack[1000];
	int spointer = 0;


	rid *method = get_child_d(bind,"method");
	rid *as = get_child_d(bind,"as");

	rid *start = method->cr;
	rid *end = start->rr;

	if(as == NULL || as->cr == NULL) as = create_rid("/");
	else as = as->cr;

	rid *before = NULL;


	while(cur != NULL ){
		if(cmp_rid(start,cur)) {

			rid *t = create_rid("");

			if(before == NULL) link_child(c_p,t);
			else before->rr = t;

			copy_rid_value(as,t);
			stack[spointer++] = c_p;
			c_p = t;

			rid *rm = cur;
			cur = cur->rr;
			free(rm);
			before = NULL;
		}
		else if(cmp_rid(end,cur)){
			before->rr = NULL;
			before = c_p;
			c_p = stack[spointer--];
			rid *rm = cur;
			cur = cur->rr;
			free(rm);
		}
		else{

			if(before == NULL) before = link_child(c_p,cur);
			else {
				before->rr = cur;
				before = cur;
			 }
			cur = cur->rr;

		}
	}

	return dummy->cr;
}

