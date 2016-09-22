

/*

//Globals and constants
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
char global[] = "this is a globval string";
const int forejendras = 1231241;

int main() {
	int pid = getpid();
	foo:
	printf("pid: %d\n" , pid);
	printf("global string: %p\n" , &global);
	printf("constant: %p\n" , &forejendras);
	printf("the code: %p\n" , &&foo);
	printf("\n\n/proc/%d/maps \n\n" , pid);
	char command [50];
	sprintf(command, "cat /proc/%d/maps", pid);
	system(command);
	return 0;



}
*/


/*
//Where are local variables? On the stack yo!

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	int pid = getpid();
	unsigned long p = 0x1;
	printf("p (0x%lx): %p\n", p, &p);
	printf("\n\n  /proc/%d/maps \n\n", pid);
	char command [50];
	sprintf(command, "cat /proc/%d/maps", pid);
	system(command);
	return 0;
}
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void zot(unsigned long *stop) {
	unsigned long r = 0x3;
	unsigned long* i;
	for ( i = &r ; i <=stop; i++){
		printf("%p 0x%lx \n", i, *i);
	}
}

void foo(unsigned long *stop) {
	unsigned long q = 0x2;
	zot(stop);
}

int main () {
	int pid = getpid();
	unsigned long p = 0x1;
	foo(&p);
	back:
	printf("p : %p\n", &p);
	printf("back : %p\n" , &&back);
	printf("\n\n /proc/%d/maps \n\n", pid);
	char command [50];
	sprintf(command, "cat /proc/%d/maps", pid);
	system(command);
	return 0;
}