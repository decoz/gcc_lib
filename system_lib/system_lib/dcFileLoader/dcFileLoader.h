/*
 * dcFileLoader.h
 *
 *  Created on: 2012. 8. 4.
 *      Author: decoz
 *
 *
 *      ���Ϸδ��� ������ ���ϸ���Ʈ�� �о� �����ϴ� ��Ȱ�� �Ѵ�.
 *      db�� ���ڵ�ó�� next() ����� �����Ѵ�.
 *
 *		��:)
 *
 *		dcFileLoader fl
 *		fl.load("images", "*.jpg");
 *		char *fname;
 *		while( ( fname = fl.next( ) != null ){
 *
 *
 *		}
 *
 */

#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include <vector>
using namespace std;

class dcFileLoader {

public:

	vector <char *> flist;

	void load(char *path); // �н�+  ���ϸ�(����) �� �Է�  ex) load("images/*.jpg " );
	char *next();			// ���� ������ ���ϳ����� �����ϰ� ���ΰ�� null �� ����
	char *getName(); 	// ���� ���õ� ������ ���ϸ��� ����
	char *getPath(); 	// ���� ���õ� ������ �н��� ����

	dcFileLoader();
	virtual ~dcFileLoader();

private:
	int cur;

	char *cutoffPath(char *str); // ���ϸ��� ������ ��θ� �и�,  �������� / ÷��
	char *pathName(char *path, char *name); // ��ο�  ���ϸ��� ���ļ� ����
};


#endif /* IMAGEMANAGER_H_ */
