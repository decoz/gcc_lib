/*
 * dsSeq.h
 *
 *  Created on: 2016. 2. 19.
 *      Author: decoz
 *
 *  넘버링을 담당하는 싱글톤 클래스
 *  파일명을 위해 계층적 Prefix, postfix 를 지원하며
 *  Prefix 별로 넘버링 리셋이 가능
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
	int 		digit_cnt;			// 숫자 자릿수 ( 3 => 001, 002, ... )

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

	void 		_setDigitCount(int cnt);									// numbering 자릿수 설정 기본:2

	static void 	setPrefix(int n, char *str, bool reset = true){		// n번째 prefix 세팅
		dsSeq::getIt()->_setPrefix(n,str,reset);
	}

	static void 	setPostfix(int n, char *str, bool reset = true){		// n번째 postfix 세팅
		dsSeq::getIt()->_setPostfix(n,str,reset);
	}

	static char*	next(){														// 다음 문자열을 받음
		return dsSeq::getIt()->_next();
	}

	static void 	setDigitCount(int cnt) {									// numbering 자릿수 설정 기본:2
		dsSeq::getIt()->_setDigitCount(cnt);
	}

};

#endif /* DCSEQ_DCSEQ_H_ */
