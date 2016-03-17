/*
 * rid.h
 *
 *  Created on: 2009. 9. 2.
 *      Author: decoz
 */
#ifndef RID_H_
#define RID_H_

#include "type.h"

#define PSIZE 4
#define SIZE 2

#define T_NORMAL 	0x01	// 데이터 영역에 데이터를 가짐
#define T_INDIRECT 	0x02	// 데이터 영역에 다른 RID를 가르치는 RID를 가짐

typedef struct _rid {
	BYTE type;
	int size;
	BYTE *addr;
	struct _rid *cr;
	struct _rid *lr;
	struct _rid *rr;
} rid ;

rid* create_rid(char *data);
rid *create_irid(rid *trid);
rid *create_rid_byte(BYTE *addr,int size);
rid *create_empty_rid();

char *create_str(rid *input);

rid	*struct_rid_c(char *data,rid *rule);
rid *struct_rid(rid *src,rid *rule);

void remove_rid(rid *trid);

void *copy_rid_value(rid *source,rid *target);
rid *copy_rid_struct_r(rid *source);

rid *link_child(rid *parent,rid *child);
rid *link_brother(rid *elder, rid *younger);

void unlink_child(rid *parent,rid *child);
void unlink_child_n(rid *parent,int child_n);
void unlink_child_all(rid *parent);


rid *get_child_n(rid *parent, int n);
int get_child_count(rid *parent);
rid *get_child_d(rid *parent, char *data);
rid *get_rid_n(rid *irid , int n);
rid *get_rid_i(rid *irid);

rid *get_rid_by_path(rid *src,BYTE *path,int pc);

rid *get_gchild(rid *parent, char *data);

rid *find_child_contains(rid *root,char *subdata);
rid *find_child_contains_r(rid *parent,char *subdata);
rid *find_path(rid *root,char *subdata);

void print_rid(rid *root);
void print_rid_r(rid *trid,int depth);
void print_single_rid(rid *trid);

int is_rid(rid *trid,char *data);
int cmp_rid(rid *trid, rid *srid);

rid *serialize_struct(rid *input);
rid *deserialize_struct(rid *input);

#endif
