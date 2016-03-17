/*
 * parser.h
 *
 *  Created on: 2009. 9. 15.
 *      Author: decoz
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "rid.h"



rid *parse(rid *src, rid *parser);
rid *create_srg_parser();

rid *tokenize(rid *target,rid *token);
rid *box(rid *target,rid *bind);
rid *seperate(rid *target,rid *sep);
rid *restruct(rid *source,rid *restruct_rid);

rid *search_direct(rid *target,rid *pat);
rid *search_indirect(rid *target,rid *pat);

rid *match_pattern_h(rid *target, rid *pat);
rid *match_pattern_r(rid *target, rid *pat);


BYTE *match_r(rid *method,BYTE *pos,BYTE *end);
int is_token_method(rid *trid);


#endif /* PARSER_H_ */
