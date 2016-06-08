#include <stdio.h>
#include "dcFileLoader/dcFileLoader.h"
#include "dsSeq/dsSeq.h"
#include "dsTime/dsTime.h"
#include "sys_util/sys_util.h"

void test_fileLoader( int argc, char **argv);
void test_seq();
void test_timer();

int main( int argc, char **argv )
{
	//test_fileLoader(argc,argv);
	//test_seq();
	test_timer();
}

void test_getline(){



}


void test_timer(){
/*
 * dsTime 테스트 함수
 */

	dsTime::start(0);

	for(int i=0;i<10000;i++){
		printf("%4d ",i);
		if(i%10 == 9) printf("\n");
	}
	fflush(stdout);

	dsTime::end(0);
	dsTime::print(0, "thousand print");

}

void test_fileLoader( int argc, char **argv){

	dcFileLoader fl;
	printf("file loader test \n");

	for(int i=1;i<argc;i++) fl.load(argv[i]);

	char *fname;
	while( ( fname = fl.next() ) != NULL){
		printf("%s // %s\n", fl.getPath(), fl.getName());
	}
}


void test_seq(){



	dsSeq::setPrefix(0,"file");
	dsSeq::setDigitCount(2);

	for(int i=0;i<20;i++){
		if(i % 4 == 0) {
			char buff[10];
			sprintf(buff,"_group%d_",i/4);
			dsSeq::setPrefix(1,buff,false);
		}
		printf("%s\n", dsSeq::next());
	}

}
