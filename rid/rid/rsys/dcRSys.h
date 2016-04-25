/*
 * dcRSys.h
 *
 *  Created on: 2016. 3. 30.
 *      Author: decoz
 *
 *  rid information 을 관리하는 시스템
 *
 *	폴더 시스템처럼 current path 를 사용함*
 *
 */

#ifndef RSYS_DCRSYS_H_
#define RSYS_DCRSYS_H_

#include <rid.h>

class dcRSys {

	rid *root, *cur, *last;  // last : 마지막 명령의 결과 rid
	rid *path[100];	// 위치
	int pcnt = 0;	// path count

private:

public:

	char 	prompt[100];

	rid*	cmd(rid* r);
	rid*	go(rid *r, rid *path);
	rid*	cut(rid *r, rid *path);
	void 	interprete(const char *input);
	void	cur_path();		// 현재 패스를 문자열로 리턴한다.

	dcRSys();
	virtual ~dcRSys();
};

#endif /* RSYS_DCRSYS_H_ */
