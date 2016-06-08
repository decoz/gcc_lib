/*
 * dsTime.h
 *
 *  Created on: 2016. 3. 2.
 *      Author: decoz
 *
 *  lab time 체크를 위한 singleton 클래스
 *
 *  사용법
 *
		dsTime::start( 0 );

		// any code //

		dsTime::end( 0 );
		dsTime::print( 0 , "time class test" );
 *
 *
 */

#ifndef DSTIME_DSTIME_H_
#define DSTIME_DSTIME_H_

#include <stdio.h>
#include <map>
#include <time.h>

using namespace  std;

typedef struct _eltime {
	time_t s_time;
	time_t e_time;
	long s_tick;
	long e_tick;
} eltime;

class dsTime {
private:
	dsTime();
	map<int, eltime*> time_table;

public:
	static dsTime* it;

	void 	_time_start(int id); 							//시간 측정 시작
	time_t 	_time_end(int id); 							//시간 측정 end
	void	_report(int id, char *subject = NULL); 	// 화면에 결과 표시

	static 	dsTime* 	getIt(){
		if(it == NULL)
			it = new dsTime();
		return it;
	}

	static 	time_t end(int id){
		return getIt()->_time_end(id);
	}

	static void 	start(int id){
		getIt()->_time_start(id);
	}

	static void 	print(int id, char *subject = NULL){
		getIt()->_report(id, subject);
	}

	virtual ~dsTime();
};


#endif /* DSTIME_DSTIME_H_ */
