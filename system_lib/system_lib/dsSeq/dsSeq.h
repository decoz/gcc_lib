/*
 * dsSeq.h
 *
 *  Created on: 2016. 2. 19.
 *      Author: decoz
 *
 *  �ѹ����� ����ϴ� �̱��� Ŭ����
 *  ���ϸ��� ���� ������ Prefix, postfix �� �����ϸ�
 *  Prefix ���� �ѹ��� ������ ����
 */

#ifndef DCSEQ_DCSEQ_H_
#define DCSEQ_DCSEQ_H_

#include <string.h>
#include <stdio.h>

using namespace std;

class dsSeq {
private:
	dsSeq();
	static dsSeq* it;
	int 		current;
	char *		prefix[10];
	char * 	postfix[10];
	int 		digit_cnt;			// ���� �ڸ��� ( 3 => 001, 002, ... )

public:
	~dsSeq();
	 static dsSeq*	getIt(){
		if( it == NULL)
			it = new dsSeq();
		return it;
	};


	void 		_setPrefix(int n, char *str, bool reset = true);
	void 		_setPostfix(int n, char *str, bool reset = true);
	char*		_next();

	void 		_setDigitCount(int cnt);									// numbering �ڸ��� ���� �⺻:2

	static void 	setPrefix(int n, char *str, bool reset = true){		// n��° prefix ����
		dsSeq::getIt()->_setPrefix(n,str,reset);
	}

	static void 	setPostfix(int n, char *str, bool reset = true){		// n��° postfix ����
		dsSeq::getIt()->_setPostfix(n,str,reset);
	}

	static char*	next(){														// ���� ���ڿ��� ����
		return dsSeq::getIt()->_next();
	}

	static void 	setDigitCount(int cnt) {									// numbering �ڸ��� ���� �⺻:2
		dsSeq::getIt()->_setDigitCount(cnt);
	}

};

#endif /* DCSEQ_DCSEQ_H_ */
