/*
 * parser_restruct.c
 *
 *  Created on: 2009. 9. 30.
 *      Author: decoz
 *
 *		from next project ... I'll change every euc-kr code to UTF-8
 */
#include "parser.h"
#include "stdlib.h"
#include "stdio.h"

rid *get_pat_irid(rid *target,rid *sch);
int cmp_pattern(rid *target , rid *sch);
rid *restruct_create_bucket_r(rid *sch, rid *cur_target, rid *bucket_end);
rid *restruct_create_bucket(rid *sch, rid *target);
rid *restruct_r(rid *source,rid *pat, rid *target);

void restruct_set_terminal_mark_r(rid *target);
void restruct_set_terminal_unmark_r(rid *target);
rid *restruct_set_r(rid *sch,  rid *target, rid *map_list);
void restruct_set(rid *sch,  rid *target);
////////////////////////////////////////////////

rid *restruct(rid *source,rid *restruct_rid){
	//print_rid(restruct_rid);

	rid *dummy = create_rid("");
	link_child(dummy,source);


	rid *restruct_cur,*target,*pattern;
	if( restruct_rid == NULL || restruct_rid->cr == NULL) return NULL;

	if( is_rid(restruct_rid->cr,"/") ) restruct_cur = restruct_rid->cr;
	else  restruct_cur = restruct_rid;

	while(restruct_cur  != NULL){
		target = get_child_d(restruct_cur,"target");
		pattern = get_child_d(restruct_cur,"pattern");

		if(target != NULL && pattern != NULL){
			restruct_r(dummy,pattern->cr,target->cr);
		}
		//printf("\n-----------------------------------------------\n");
		//print_rid(source);

		restruct_cur = restruct_cur->rr;
	}

	return dummy->cr;
}

rid *restruct_r(rid *source,rid *pat, rid *target){


	rid *cur = source;

	rid *sch = NULL;


	rid *match = match_pattern_r(source,pat);

	while(match!=NULL){
		rid *tgt = copy_rid_struct_r(target);
		sch = get_pat_irid(match,pat);
		restruct_set(sch,tgt);

		rid *src = get_rid_i(sch);
		src->addr = tgt->addr;
		src->size = tgt->size;
		src->rr = tgt->rr;
		src->cr = tgt->cr;

		match = match_pattern_r(source,pat);
	}

	if(source->cr != NULL){
		restruct_r(source->cr,pat,target);
	}
	if(source->rr != NULL){
		restruct_r(source->rr,pat,target);
	}

}


void restruct_set_terminal_mark_r(rid *target){
	if(target->cr == NULL){
		target->type += 100;
	}
	else restruct_set_terminal_mark_r(target->cr);
	if(target->rr != NULL) restruct_set_terminal_mark_r(target->rr);
}

void restruct_set(rid *sch,  rid *target){
	rid *map_list = restruct_create_bucket(sch,target);
	restruct_set_terminal_mark_r(target);

		/*
		printf("\n=======================map created======================\n");
		print_rid(map_list);
		printf("\n========================================================\n");
		*/

	rid *left = restruct_set_r(sch,target,map_list);

	rid *t = target;
	while(t->type < 100) t = t->cr;
	if(left != NULL){
		link_child(t,left->cr);
		link_brother(target,left->rr);
	}
	else {printf("error.restruct_set.restruct fail\n");}


	restruct_set_terminal_unmark_r(target);
}

void restruct_set_terminal_unmark_r(rid *target){

	if(target->type > 100) {
		target->type -= 100;
	}
	else if(target->cr != NULL) restruct_set_terminal_unmark_r(target->cr);
	if(target->rr != NULL) restruct_set_terminal_unmark_r(target->rr);

}


rid *restruct_create_bucket(rid *sch, rid *target){
	 rid *bucket = create_rid("/");
	 restruct_create_bucket_r(sch,target,bucket);
	 return bucket;

}

rid *restruct_create_bucket_r(rid *sch, rid *cur_target, rid *bucket_end){
	rid *result;

	if(cur_target->cr != NULL)
		bucket_end = restruct_create_bucket_r(sch,cur_target->cr,bucket_end);
	if(cur_target->rr != NULL)
		bucket_end = restruct_create_bucket_r(sch,cur_target->rr,bucket_end);

	if(cur_target->addr[0] == '$'){

		rid *temp = get_rid_by_path(sch,cur_target->addr,cur_target->size);
		if(temp!=NULL){
			result = create_irid(temp);
			link_child(result,create_irid(cur_target));
		}

		if(bucket_end == NULL)bucket_end = result;
		else bucket_end->rr = result;

		return result;
	}

	return bucket_end;

}


rid *restruct_set_r(rid *sch,  rid *target, rid *map_list){

	if(map_list == NULL || sch == NULL) return NULL;

	rid *c_result=NULL,*r_result=NULL;
	rid *src = get_rid_i(sch);
	rid *result = create_rid("/");

	if(sch->cr != NULL){
		rid *t = src->cr;
		while(t!=NULL && t->rr != get_rid_i(sch->cr)) t = t->rr;

		if(t!=NULL) t->rr = NULL;
		else src->cr = NULL;

		c_result = restruct_set_r(sch->cr,target,map_list);
		link_child(src,c_result->cr);
		link_child(src,c_result->rr);
	}

	if(sch->rr != NULL){
		r_result = restruct_set_r(sch->rr,target,map_list);
		link_brother(src->cr,r_result->cr);
		src->rr = r_result->rr;
	}


	//printf("restruct_set_r.search:");print_single_rid(sch);printf("\n");

	rid *map_t = map_list->rr;
	rid *map_sch;

	rid *match = NULL;
	while(map_t != NULL){
		map_sch = get_rid_i(map_t);
		/*
		rid *b1,*b2;
		b1 = sch;
		b2 = get_rid_i(temp_rid);
		BYTE *a1 = get_rid_i(cur_pat)->addr;
		BYTE *a2 = get_rid_i(sch_rid)->addr;


		printf("restruct_set_r.matching_mlist:	");
					print_single_rid(map_sch);
					printf("\n");

		*/
		if(map_sch == sch){
			match = map_t;
		}

		map_t = map_t->rr;
	}


	if(match != NULL) {
		/*
		printf("restruct_set_r.match:");
		print_single_rid(get_rid_i(match));
		printf("\n");
		*/

		rid *tgt = get_rid_i(match->cr);
		tgt->addr = src->addr ;
		tgt->size = src->size;


		while(tgt->cr != NULL && tgt->type < 100 ) tgt = tgt->cr;
		tgt->cr = link_brother(src->cr,tgt->cr);
		//link_child(tgt,src->cr);
		result->rr = src->rr;
		tgt->type = T_NORMAL+100;
		return result;
	}
	else {
		//printf("restruct_set_r.report:no_match:\n");
		result->cr = src->cr;
		result->rr = src->rr;
		return result;
	}

	return NULL;

}


rid *search_indirect(rid *target,rid *pat){
	rid *match  = search_direct(target,pat);
	return get_pat_irid(match,pat);
}

rid *get_pat_irid(rid *target,rid *sch){

	//rid *result;
	rid *cur = match_pattern_h(target,sch);
	rid *cur_pat = sch;

	/*
		printf("call-");
		print_single_rid(target);
		printf("\n");
	*/



	rid *lp = NULL;
	rid *iroot = NULL;


	while(cur!=NULL && cur_pat!=NULL){

		if(iroot != NULL) {
			lp->rr = create_irid(cur);
			lp = lp->rr;
		}
		else iroot = lp = create_irid(cur);
	
		if(cur_pat->cr != NULL){
			if(cur->cr == NULL) return NULL;

			if( (lp->cr = get_pat_irid(cur->cr,cur_pat->cr)) == NULL )
				return NULL;
		}		

		cur = cur->rr;
		cur_pat = cur_pat->rr;

	}

	if(cur==NULL && cur_pat!=NULL) return NULL;
	else return iroot;

}



rid *search_direct(rid *target,rid *pat){

	rid *cur = target;
	rid *match = match_pattern_r(target,pat);

	if(match != NULL ) return match;
	else if(cur == NULL) return NULL;
	else {
		while(cur != NULL){
			match = search_direct(cur->cr,pat);
			if(match != NULL) return match;
			cur = cur->rr;
		}
		return NULL;
	}
}


rid *match_pattern_r(rid *target, rid *pat){

	//rid *result;
	rid *match = match_pattern_h(target,pat);
	rid *cur = match;
	rid *cur_pat = pat;

	/*
		debug print

			printf("[");
			print_single_rid(target);
			printf(":");
			print_single_rid(pat);
			printf("]--");
			print_single_rid(match);
			printf("--\n");

	*/


		if(match != NULL){

			while(cur_pat != NULL && cur != NULL){
				if(cur_pat->cr == NULL || match_pattern_r(cur->cr,cur_pat->cr) != NULL){
					cur = cur->rr;
					cur_pat = cur_pat->rr;
				}
				else {
					match = match_pattern_h(match -> rr,pat);
					cur = match;
					cur_pat = pat;
				}

				if(cur == NULL && cur_pat != NULL) return NULL;
			}
			return match;
		}
		else return NULL;
}

rid *match_pattern_h(rid *target, rid *pat){

	rid *cur, *cur_start, *cur_pat;

	cur = target;
	cur_pat = pat;
	cur_start = target;

	while(cur_pat != NULL && cur != NULL){
		if(cmp_pattern(cur,cur_pat)) {
			cur = cur->rr;
			cur_pat = cur_pat->rr;
		}
		else {
			cur = cur_start = cur_start->rr;
			cur_pat = pat;
		}

	}

	if( cur_pat == NULL ) return cur_start;
	else return NULL;

}



int cmp_pattern(rid *src , rid *pat){
	/*
	printf("[");
	print_single_rid(target);
	printf(":");
	print_single_rid(pat);
	printf("]");
	*/

	int i;
	if(is_rid(pat,"?"))	return 1;

	BYTE *src_str = src->addr;
	BYTE *pat_str = pat->addr;
	if( pat_str[0] == '!' ){
		if(pat->size != src->size + 1) return 1;
		for(i=0;i<src->size;i++){
			if(src_str[i] != pat_str[i+1]) return 1;
		}
		return 0;
	}
	else {
		if(pat->size != src->size) return 0;
		for(i=0;i<src->size;i++){
			if(src_str[i] != pat_str[i]) return 0;
		}
		return 1;
	}

	if(cmp_rid(src,pat)) {
		//printf("@");
		return 1;
	}
	else return 0;



}

