/*
//fork returns 2 values!
#include <stdio.h>
#include <unistd.h>

int main() {
	int pid = fork();
	printf("pid = %d\n", pid);
	return 0;
}
*/

/*
//Turns out that the child and mother have different pids
#include <stdio.h>
#include <unistd.h>

int main() {
	int pid = fork();
	if(pid == 0 ) {
		printf("im the child! %d\n", getpid());
		sleep(1);
	} else {
		printf("My child is called %d\n", pid);
	}
	printf("Thats it! %d\n", getpid());
	return 0;
}
*/

/*
//Same adress but in different cities! ...or virtual pages, in this case...
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	int pid;
	int x = 123;
	pid = fork();

	if(pid == 0 ) {
		printf("child: %d and the address is 0x%p\n", x, &x);
		x = 42;
		sleep(1);
		printf("child: %d and the address is 0x%p\n", x, &x);
	} else {
		printf("mother: %d and the address is 0x%p\n", x, &x);
		x=13;
		sleep(1);
		printf("mother: %d and the address is 0x%p\n", x, &x);
		wait(NULL);
	}
	printf("This is the end (%d)\n", getpid());
	return 0;
}

*/

/*
//Who's your daddy? The shell appearantly!
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	int pid = fork();
	if(pid==0){
		printf("im the child %d with parent %d\n", getpid(), getppid());
	} else {

		printf("im the parent %d with parent %d\n", getpid(), getppid());
		wait(NULL);
	}
	return 0;
}
*/
/*
//Both familymebers are in the same group!
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	int pid = fork();
	if(pid==0){
		int child = getpid();
		printf("im the child %d in group %d\n", child, getpgid(child));
	} else {

		int parent = getpid();
		printf("im the parent %d in group %d\n", parent, getpgid(parent));
		wait(NULL);
	}
	return 0;
}
*/


//Parent died so the child became an orphan, then it was adopted by upstart!
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	int pid = fork();
	if(pid == 0){
		int child = getpid();
		printf("chuld : parent %d ,  in group %d\n", getppid(), getpgid(child));
		sleep(4);
		printf("chuld : parent %d ,  in group %d\n", getppid(), getpgid(child));
		sleep(4);
		printf("chuld : parent %d ,  in group %d\n", getppid(), getpgid(child));
		sleep(4);
	} else {
		int parent = getpid();
		printf("parent : parent %d ,  in group %d\n", getppid(), getpgid(parent));
		sleep(2);
		int zero = 0;
		int i = 3 / zero;
	}
	return 0;
}