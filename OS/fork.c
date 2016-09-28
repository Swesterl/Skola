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

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	int pid;
	int x = 123;
	pid = fork();

	if(pid == 0 ) {
		printf("child: %d\n", x);
		x = 42
		sleep(1);
		printf("child: %d\n", x);
	} else {
		printf("Mother :  %d\n", x);
		x=13;
		sleep(1);
		printf("Mother :  %d\n", x);
		wait(NULL);
	}
	printf("This is the end (%d)\n", getpid());
	return 0;
}