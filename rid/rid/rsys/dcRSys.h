/*
 * dcRSys.h
 *
 *  Created on: 2016. 3. 30.
 *      Author: decoz
 *
 *  rid information �� �����ϴ� �ý���
 *
 *	���� �ý���ó�� current path �� �����*
 *
 */

#ifndef RSYS_DCRSYS_H_
#define RSYS_DCRSYS_H_

#include <rid.h>

class dcRSys {

	rid *root, *cur, *last;  // last : ������ ����� ��� rid
	rid *path[100];	// ��ġ
	int pcnt = 0;	// path count

private:

public:

	char 	prompt[100];

	rid*	cmd(rid* r);
	rid*	go(rid *r, rid *path);
	rid*	cut(rid *r, rid *path);
	void 	interprete(const char *input);
	void	cur_path();		// ���� �н��� ���ڿ��� �����Ѵ�.

	dcRSys();
	virtual ~dcRSys();
};

#endif /* RSYS_DCRSYS_H_ */
