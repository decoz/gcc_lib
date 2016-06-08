/*
 * cfg.h
 *
 *  Created on: 2016. 3. 14.
 *      Author: decoz
 *
 *  config 설정을 제공하는 싱글톤 클래스
 *  레지스트리처럼 특정 노드의 존재 여부 및
 *  그 값을 통해 config 설정가능
 *
 *  사용법은
 *
 *  cfg::set("debug.process1");
 *  cfg::put("cfg.val1","10");
 *
 *  if (  cfg::is("debug.process1") ) {
 *  	... 	// debug code
 *  	cfg::get("cfg:val1"); *
 *  }
 *
 *
 *
 */

#ifndef DSCFG_CFG_H_
#define DSCFG_CFG_H_
#include <stdio.h>
#include "rid.h"

class cfg {
private:
	cfg();
	rid *root, *cur;

public:

	static cfg *it;

	static cfg* getIt(){
		if(it == NULL)
			it = new cfg();
		return it;
	}

	void 	_set(char *path, char *value);	// 경로에 값을  세팅함 (경로가 없을경우 경로를 만듬)
	bool 	_is(char *p);					// 경로가 존재하는지 추적
	bool	_put(char *p, char *v);			// 경로에 값을 세팅하되 경로가 없으면 false 리턴
	char*	_get(char* path);				// 경로의 값을 얻어옴 .. 없으면 NULL
	void 	_loadfile(char *fname, bool appand);		// 파일 구조를 읽음
	void 	_savefile(char *fname, char* p = NULL);				// 경로의 내용을 파일에 저장 (경로 없으면 전체 저장)
	void 	_print();

	static void	loadfile(char *fname, bool appand = false){
		getIt()->_loadfile(fname, appand);
	}

	static char* get(char* path){
		return getIt()->_get(path);
	}

	static int getint(char *path){
		char *s = getIt()->_get(path);
		if(s!=NULL) return atoi(s);
		else return 0;
	}

	static float getfloat(char *path){
		char *s = getIt()->_get(path);
		if(s!=NULL) return atof(s);
		else return 0;
	}


	static bool is(char *path){
		return getIt()->_is(path);
	}

	static void print(){
		getIt()->_print();
	}

	virtual ~cfg();

};

#endif /* DSCFG_CFG_H_ */
