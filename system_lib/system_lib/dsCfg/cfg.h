/*
 * cfg.h
 *
 *  Created on: 2016. 3. 14.
 *      Author: decoz
 *
 *  config ������ �����ϴ� �̱��� Ŭ����
 *  ������Ʈ��ó�� Ư�� ����� ���� ���� ��
 *  �� ���� ���� config ��������
 *
 *  ������
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

	void 	_set(char *path, char *value);	// ��ο� ����  ������ (��ΰ� ������� ��θ� ����)
	bool 	_is(char *p);					// ��ΰ� �����ϴ��� ����
	bool	_put(char *p, char *v);			// ��ο� ���� �����ϵ� ��ΰ� ������ false ����
	char*	_get(char* path);				// ����� ���� ���� .. ������ NULL
	void 	_loadfile(char *fname, bool appand);		// ���� ������ ����
	void 	_savefile(char *fname, char* p = NULL);				// ����� ������ ���Ͽ� ���� (��� ������ ��ü ����)
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
