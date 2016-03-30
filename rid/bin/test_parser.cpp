/*
 * console.c
 *
 *  Created on: 2009. 9. 2.
 *      Author: decoz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rid.h"
#include "rid_io.h"

#include "parser.h"

void basic_rid_test();
rid *tokenize_test();
void bind_test();
rid *seperate_test();
rid *search_pattern_test(rid *input);
void match_pattern_h_test(rid *input);
void create_irid_test();
void parser_zero_test();
void serialize_test();
void put_rid_test();

int main(void) {

	/*
	rid *fname = create_rid("packet.psr");
	rid *frid = create_rid_f(fname);
	printf("%d\n",frid->size);
	print_rid(frid);
	*/

	//parser_zero_test();
	put_rid_test();

	/*
	rid *p = create_srg_parser();
	srg_print(p);
	*/

	/*
	rid *rstruct = deserialize_struct(frid);

	print_rid(rstruct);


	serialize_test();
	*/

	return 0;
}


void put_rid_test(){

	rid *data = struct_rid_c("a(b,c,d)",NULL);

	put_rid(data, struct_rid_c("b(b1,b2),c(c1,c2),e", NULL));
	print_rid(data);

}

void serialize_test(){
	rid *data = struct_rid_c("adam(eve,a(date1,date2),alpa(beta,gama))",NULL);
	//rid *data = struct_rid_c("adam(eve,nako,alpa.beta)",NULL);

	rid *t = serialize_struct(data);
	rid *new_r = deserialize_struct(t);
	print_rid(new_r);

}


void parser_zero_test(){
	rid *data = struct_rid_c("x(adam,nako,alpa.beta)",NULL);
	print_rid(data);
	//srg_print(data);
}

void create_irid_test(){

	rid *data = create_rid("data");
	rid *idata = create_irid(data);
	rid *t = (rid*) idata->addr;
	print_rid(idata);

}


void match_pattern_h_test(rid *input){

	printf("--------------------input-----------------------\n");
	print_rid(input);

	rid *data = create_rid("data");
	link_child(data,create_rid("A"));
	link_child(data,create_rid("B"));

	rid *temp = link_child(data,create_rid("C"));
		link_child(temp,create_rid("F"));

	link_child(data,create_rid("D"));
	link_child(data,create_rid("E"));

	//temp = link_child(pat,create_rid("C"));

	printf("--------------------output-----------------------\n");
	rid *pat = create_rid("/");
	link_child(pat,create_rid("Baby"));
	link_child(pat,create_rid("."));
	print_rid(search_indirect(input,pat));

}


rid *search_pattern_test(rid *input){

	print_rid(input);
	//input = create_rid("Babo");

	rid *pattern = create_rid("/");
	link_child(pattern,create_rid("Adam"));
	//match_pattern_r(input,pattern);
	print_rid(match_pattern_r(input,pattern));

	return NULL;
}

void basic_rid_test(){

	/////////// Test Basic tree structure 1 ////////////////

	rid *t = create_rid("hi");
	rid *t1 = create_rid("c1");
	rid *t2 = create_rid("c2");
	rid *t3 = create_rid("c3");

	link_child(t,t1);
	printf("now count %d \n",get_child_count(t));

	link_child(t,t2);
	printf("now count %d \n",get_child_count(t));

	link_child(t,t3);
	printf("now count %d \n",get_child_count(t));

	//////////////////////////////////////////////////////*/
	printf("rid test console start\n");


	/*0903 unlink test
	unlink_child(t,t2);
	unlink_child_n(t,0);
	unlink_child_all(t);

	print_rid(t);
	*/

	/////////////////////////////////////////////////////////
	/* 08?? print_rid test
	print_single_rid( get_child_n(t,0));
	print_single_rid( get_child_n(t,1));
	print_single_rid( get_child_n(t,3));

	print_single_rid( find_child_contains(t,"c1"));
	*/


	/////////////////////////////////////////////////////////
	//	0907 contains test
	//printf("\n[Debug:0907] match test : %d", contains("testtest",8,"tte",2));



	/////////////////////////////////////////////////////////
	//	0915  is_rid test
	//if(is_rid(t,"ho")) printf("\n[Debug:0915] OK t is hi\n");

}

rid *seperate_test(){

	rid *data = create_rid("root( Adam, Babo,Baby(Amateras,middle),C)");
	rid *rid_tok = create_rid("token");
	rid *r1 = create_rid("");
	rid *r2 = create_rid("");
	rid *r3 = create_rid("");
	rid *r4 = create_rid("");
	rid *pos;

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


	rid *r3_method = create_rid("method");
		link_child(r3,r3_method);
		link_child(r3_method,create_rid(","));

	rid *r4_method = create_rid("method");
			link_child(r4,r4_method);
			link_child(r4_method,create_rid("."));

	link_child(rid_tok,r1);
	link_child(rid_tok,r2);
	link_child(rid_tok,r3);
	link_child(rid_tok,r4);

	rid *result = tokenize(data,rid_tok);
	printf("\n");
	print_rid(result);

	rid *b = create_rid("box");
	pos = link_child(b,create_rid("method"));
		link_child(pos,create_rid("("));
		link_child(pos,create_rid(")"));
	rid *result2 = box(result,b);
	printf("\n");
	print_rid(result2);

	rid *s = create_rid("seperate");
		pos = link_child(s,create_rid("method"));
		link_child(pos,create_rid(","));

	printf("\n");
	rid *result3 = seperate(result2,s);
	print_rid(result3);

	printf("\n========================end seperate test======================\n");
	//print_rid(NULL);
	return result3;

}


void bind_test(){

	/////////////////////////////////////////////////////////
	//	0920 bind test
	/////////////////////////////////////////////////////////

	rid *data = create_rid("A(ABA (AC D))");

	rid *rid_tok = create_rid("token");
	rid *r1 = create_rid("");
	rid *r2 = create_rid("");
	rid *pos;

	rid *r1_method = create_rid("method");
	link_child(r1,r1_method);
	pos = link_child(r1_method,create_rid("or"));
		link_child(pos,create_rid("("));
		link_child(pos,create_rid(")"));

	rid *r2_method = create_rid("method");
	link_child(r2,r2_method);
		pos = link_child(r2_method,create_rid("+"));
			pos = link_child(pos,create_rid("-"));
					link_child(pos,create_rid("A"));
					link_child(pos,create_rid("Z"));


	link_child(rid_tok,r1);
	link_child(rid_tok,r2);

	printf("[debug:0918] bind test \n");
	print_rid(rid_tok);

	rid *result = tokenize(data,rid_tok);
	print_rid(result);

	rid *b = create_rid("box");
	pos = link_child(b,create_rid("method"));
		link_child(pos,create_rid("("));
		link_child(pos,create_rid(")"));


	print_rid(box(result,b));

	printf("[debug:end]\n");


}

rid *tokenize_test(){
	/////////////////////////////////////////////////////////
		/*
		 * 	0915 token_test v 0.1
		 */
		rid *data = create_rid("ADABAACD");
		rid *rid_tok = create_rid("token");


		rid *r = create_rid("");
			rid *r1 = create_rid("method");
			rid *r11 = create_rid("+");
			r11->cr = create_rid("A");
			link_child(r1,r11);

			rid *r111 = create_rid("or");
			link_child(r111,create_rid("C"));
			link_child(r111,create_rid("B"));
			link_child(r111,create_rid("D"));
			link_child(r11,r111);

		link_child(r,r1);
		link_child(rid_tok,r);


		printf("[debug:0915] token test \n");
		print_rid(rid_tok);
		rid *result = tokenize(data,rid_tok);
		print_rid(result);

		printf("[debug:end]\n");
		/////////////////////////////////////////////////////////
		return result;
}


void match_pattern_test(){
	/////////////////////////////////////////////////////////
		/*
		 * 	0915 token_test v 0.1
		 */
		rid *data = create_rid("ADABAACD");
		rid *rid_tok = create_rid("token");


		rid *r = create_rid("");
			rid *r1 = create_rid("method");
			rid *r11 = create_rid("+");
			r11->cr = create_rid("A");
			link_child(r1,r11);

			rid *r111 = create_rid("or");
			link_child(r111,create_rid("C"));
			link_child(r111,create_rid("B"));
			link_child(r111,create_rid("D"));
			link_child(r11,r111);

		link_child(r,r1);
		link_child(rid_tok,r);


		printf("[debug:0915] token test \n");
		print_rid(rid_tok);
		rid *result = tokenize(data,rid_tok);
		print_rid(result);

		printf("[debug:end]\n");
		/////////////////////////////////////////////////////////
}


void srg_print_r(rid *trid,int depth){

	int i;
	int c = get_child_count(trid);

	for(i=0;i<depth;i++) printf("   ");

	for(i=0;i<trid->size;i++){
		printf("%c",trid->addr[i]);
	}
	if(i == 0) printf("/");
	printf("\n");

	if(trid->cr != NULL){
		srg_print_r(trid->cr,depth + 1);
	}

	if(trid->rr != NULL){
		srg_print_r(trid->rr,depth);
	}

}



void srg_print(rid *r){
	srg_print_r(r,0);
}
