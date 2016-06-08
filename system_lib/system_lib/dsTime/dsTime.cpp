/*
 * dsTime.cpp
 *
 *  Created on: 2016. 3. 2.
 *      Author: decoz
 */

#include "dsTime.h"

dsTime *dsTime::it = NULL;

dsTime::dsTime() {
	// TODO Auto-generated constructor stub

}

dsTime::~dsTime() {
	// TODO Auto-generated destructor stub
}

void dsTime::_time_start(int id) { 		//시간 측정 시작
	time_t now;
	time(&now);

	long stick = clock();
	time_table[id]  =  new eltime { now, 0, stick, 0 } ;
}

time_t dsTime::_time_end(int id) {		//시간 측정 end
	time_t now;
	time(&now);

	if(time_table[id] == NULL) return -1;

	long etick = clock();
	time_table[id]->e_tick = etick;
	time_table[id]->e_time = now;

	return etick- time_table[id]->s_tick;
}

void	dsTime::_report(int id, char *subject) {
	eltime *et = time_table[id];
	char buff[30];

	if(et == NULL) {
		printf("[dsTime::error] illegal id\n");
		return;
	}

	if(subject != NULL) 	printf("[%s] ", subject);
	printf("report time elapsed\n");

	time_t stime = et->s_time;
	strftime(buff, 30, "%H:%M:%S", localtime( &stime) );
	printf("\tstart time: %s\n", buff);

	if(!et->e_time) {
		printf("it is still running \n");
		return;
	}

	time_t etime = et->e_time;
	strftime(buff, 30, "%H:%M:%S", localtime( &etime) );
	printf("\tstart time: %s\n", buff);

	printf("\trunning time:%d millisecond\n", et->e_tick - et->s_tick);


}
