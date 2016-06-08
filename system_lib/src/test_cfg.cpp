#include <stdio.h>
#include "dsCfg/cfg.h"

int main( int argc, char **argv )
{

	cfg::loadfile("test.cfg");
	printf("%d\n",cfg::getint("value1"));
	printf("%s\n",cfg::get("test_cfg.test.value1"));

	printf("%d\n",cfg::is("test_cfg.let.go1"));
	return 0;
}
