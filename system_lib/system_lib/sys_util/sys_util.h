/*
 * sys_util.h
 *
 *  Created on: 2016. 3. 8.
 *      Author: decoz
 *
 *  general library ����
 *
 */
#ifndef SYS_UTIL_H_
#define SYS_UTIL_H_

int  	getLine(char* buff, int max);				// console �κ��� �� ������ �Է¹޾� buff�� ���� �� ũ�⸦ ����
char 	*euc2utf(char *buff);
char 	*utf2euc(char *buff);
int 	IconvString (char *from, char *to, const char *src, char *dst);


#endif /* SYS_UTIL_H_ */
