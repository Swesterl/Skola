#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	int pid = fork();
	if(pid == 0){
		execlp("ls", "ls" , NULL);
		printf("this will onely happen if exec failss \n");

	} else {
		wait(NULL);
		printf("We are done \n");
	}
	return 0;
}