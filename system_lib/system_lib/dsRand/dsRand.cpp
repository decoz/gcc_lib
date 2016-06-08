/*
 * dsRand.cpp
 *
 *  Created on: 2016. 5. 23.
 *      Author: decoz
 */

#include "dsRand.h"
#include <time.h>
#include <stdlib.h>

rnd *rnd::it = NULL;

rnd::rnd() {
	// TODO Auto-generated constructor stub
	srand(time(NULL));
}

rnd::~rnd() {
	// TODO Auto-generated destructor stub
}

