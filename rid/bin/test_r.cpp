#include "rid.h"
#include "rid_io.h"

int main(){

	rid *nr = create_rid_f(create_rid("test.cfg"));
	rid *rr = rtab(nr);

/*
	rid *nr = create_rid("a(b(c,d.d1),e.f)");
	rid *pr = rstr(nr);
*/
	print_rid(rr);


}
