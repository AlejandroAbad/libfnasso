#include "../fnasso.h"
#include "../fnasso_defs.h"

#include <mcheck.h>
#include <stdio.h>

	
int main(int argc, char** argv)
{
	//mtrace();
	int v;
	printf("%s\n", fnasso_version(&v));
	printf("%d\n", v);
	
	utils();
	hashing();
	encoding();
		  
	user();
	kdc();
	//kadmin();
	
	//muntrace();
}

