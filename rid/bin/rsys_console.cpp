#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "rid.h"
#include "rid_io.h"
#include <iostream>
#include "parser.h"
#include "rsys/dcRSys.h"

using namespace std;



int main(){

	dcRSys rsys;
	printf("start rsys_console \n");

	string buff;
	cout << rsys.prompt;
	while(std::getline(std::cin,buff))
	{

	    //std::cout << buff << "\n"; //echo

		rsys.interprete(buff.c_str());
		cout << rsys.prompt << " ";

	}

	return 0;

}

