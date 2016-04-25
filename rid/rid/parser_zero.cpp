/*
 * parser_zero.c
 *
 *  Created on: 2009. 11. 24.
 *      Author: decoz
 */

#include "parser.h"
rid *create_token_rid();
rid *create_box_rid();
rid *create_sep_rid();
rid *create_restruct_rid();

rid *create_box_rid(){
	rid *b = create_rid("box");
	rid *pos = link_child(b,create_rid("method"));
			link_child(pos,create_rid("("));
			link_child(pos,create_rid(")"));
	pos = link_child(b,create_rid("method"));
			link_child(pos,create_rid("["));
			link_child(pos,create_rid("]"));
    return b;
}

rid *create_sep_rid(){
	rid *s = create_rid("seperate");
	rid *pos = link_child(s,create_rid("method"));
		link_child(pos,create_rid(","));

	return s;
}

rid *create_restruct_rid(){


	rid *pattern,*target,*temp;

	rid *rrid = create_rid("restruct");

	rid *r1,*r2,*r3;

	r1 = create_rid("/");
		link_child(r1,pattern = create_rid("pattern"));
		link_child(r1,target = create_rid("target"));

		temp = link_child(pattern,create_rid("!/"));
		link_brother(temp,create_rid("/"));

		temp = link_child(target,create_rid("$0"));
			link_child(temp,create_rid("$1"));


	r2 = create_rid("/");
		link_child(r2,pattern = create_rid("pattern"));
		link_child(r2,target = create_rid("target"));

		temp = link_child(pattern,create_rid("?"));
			link_brother(temp,create_rid("."));
			link_brother(temp,create_rid("?"));

		temp = link_child(target,create_rid("$0"));
			link_child(temp,create_rid("$2"));


	r3 = create_rid("/");
		link_child(r3,pattern = create_rid("pattern"));
		link_child(r3,target = create_rid("target"));

		temp = link_child(pattern,create_rid("!/"));
		link_child(temp,create_rid("/"));

		temp = link_child(target,create_rid("$0"));

	link_child(rrid,r1);
	link_child(rrid,r2);
	link_child(rrid,r3);

	return rrid;

}

/*
rid *parse_zero(rid *src){

	int debug = 0;
	rid *result = tokenize(src,create_token_rid());

	if(debug){
		printf("\n==================tokenize====================\n");
		print_rid(result);
	}


	result = box(result, create_box_rid());
	if(debug){
		printf("\n==================box=========================\n");
		print_rid(result);
	}

	result = seperate(result,create_sep_rid());
	if(debug){
		printf("\n==================sep=========================\n");
		print_rid(result);
	}


	result = restruct(result,create_restruct_rid());
	if(debug){
		printf("\n==================restruct=====================\n");
		print_rid(result);
	}

	return result;

}

*/


rid *create_srg_parser(){
	rid *parser = create_rid("parser");
	link_child(parser,create_token_rid());
	link_child(parser,create_box_rid());
	link_child(parser,create_sep_rid());
	link_child(parser,create_restruct_rid());

	return parser;
}


rid *create_token_rid(){
	rid *pos;

	rid *r1 = create_rid("");
	rid *r2 = create_rid("");
	rid *r3 = create_rid("");
	rid *r4 = create_rid("");
	rid *r5 = create_rid("");

	rid *rid_tok = create_rid("tokenize");

	rid *r1_method = create_rid("method");
	link_child(r1,r1_method);
	pos = link_child(r1_method,create_rid("or"));
		link_child(pos,create_rid("("));
		link_child(pos,create_rid(")"));


	rid *r2_method = create_rid("method");
	link_child(r2,r2_method);
		pos = link_child(r2_method,create_rid("+"));
		pos = link_child(pos,create_rid("or"));
			rid *pos1 = link_child(pos,create_rid("-"));
				link_child(pos1,create_rid("A"));
				link_child(pos1,create_rid("Z"));
			rid *pos2 = link_child(pos,create_rid("-"));
				link_child(pos2,create_rid("a"));
				link_child(pos2,create_rid("z"));
			rid *pos3 = link_child(pos,create_rid("-"));
				link_child(pos3,create_rid("0"));
				link_child(pos3,create_rid("9"));

	rid *r3_method = create_rid("method");
		link_child(r3,r3_method);
		link_child(r3_method,create_rid(","));

	rid *r4_method = create_rid("method");
			link_child(r4,r4_method);
			link_child(r4_method,create_rid("."));

	rid *r5_method = create_rid("method");
		link_child(r5,r5_method);
		pos = link_child(r5_method,create_rid("or"));
		link_child(pos,create_rid("["));
		link_child(pos,create_rid("]"));
		/*
		link_child(pos,create_rid("/"));
		link_child(pos,create_rid("@"));
		link_child(pos,create_rid("$"));
		link_child(pos,create_rid("#"));
		link_child(pos,create_rid("?"));
		link_child(pos,create_rid("*"));
		link_child(pos,create_rid("-"));
		link_child(pos,create_rid("_"));
		link_child(pos,create_rid("\\"));
		link_child(pos,create_rid("%"));
		*/


	link_child(rid_tok,r1);
	link_child(rid_tok,r2);
	link_child(rid_tok,r3);
	link_child(rid_tok,r4);
	link_child(rid_tok,r5);

	//print_rid(rid_tok);
	return rid_tok;

}

