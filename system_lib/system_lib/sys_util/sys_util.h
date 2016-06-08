/*
 * sys_util.h
 *
 *  Created on: 2016. 3. 8.
 *      Author: decoz
 *
 *  general library 모음
 *
 */
#ifndef SYS_UTIL_H_
#define SYS_UTIL_H_

int  	getLine(char* buff, int max);				// console 로부터 한 라인을 입력받아 buff에 저장 그 크기를 리턴
char 	*euc2utf(char *buff);
char 	*utf2euc(char *buff);
int 	IconvString (char *from, char *to, const char *src, char *dst);


#endif /* SYS_UTIL_H_ */
