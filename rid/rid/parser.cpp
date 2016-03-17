/*
 * parser.c
 *
 *  Created on: 2009. 11. 26.
 *      Author: decoz
 */

#include "stdlib.h"
#include "parser.h"

rid *parse(rid *src,rid *parser){

	if(parser == NULL)  parser = create_srg_parser();

	rid *t_result = src;
	//print_rid(t_result);


	rid *p_cur = parser->cr;
	while(p_cur != NULL){
		if(is_rid(p_cur,"seperate"))
			t_result = seperate(t_result,p_cur);

		if(is_rid(p_cur,"box"))
			t_result = box(t_result,p_cur);

		if(is_rid(p_cur,"restruct"))
			t_result = restruct(t_result,p_cur);

		if(is_rid(p_cur,"tokenize"))
			t_result = tokenize(t_result,p_cur);

		p_cur = p_cur->rr;
	}


	return t_result;
}
