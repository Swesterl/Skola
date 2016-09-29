/*

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int volatile count;

void handler (int sig) {
	printf("Signal %d ouch that hurt \n", sig);
	count++;
} 

int main()
{
	while(1){

	}

}

*/

/*
//We decide how to handle divide by zero!
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler (int sig) {
	printf("Signal %d was caught \n", sig);
	
}

int not_so_good() {
	int x = 0;
	int ans =  1%0;
	return ans;
}

int main() {
	struct sigaction sa;
	printf("Ok lets go- ill catch my own error! \n");
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	//and now we catch.... fpe signals 
	sigaction(SIGFPE, &sa, NULL);
	not_so_good();
	printf("Will probably not writ this.\n");
	return 0;
}
*/

/*
//Thanks to conext and siginfo we know who the killer is!
#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <unistd.h>

int volatile done;

void handler();

int main () {
	struct sigaction sa;
	int pid = getpid();
	printf("Ok lets go - kill me (%d) and ill tell you who you are \n", 
		pid);
	//we are using the more elavoreate sigactionhandler
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) != 0){
		return 1;
	}

	while(!done){

	}
	printf("told you so\n");
	return 0;

}

void handler (int sig, siginfo_t *siginfo, void *context){
	printf("signal %d was caught \n", sig);

	printf("your UID is %d\n", siginfo -> si_uid);

	printf("your PID is %d\n", siginfo -> si_pid);

	done = 1;
}
*/

#define _GNU_SOURCE 
#include <stdio.h>
#include <signal.h>
#include <ucontext.h>

static void handler (int signo, siginfo_t *info, void *cntx){
	ucontext_t *context = (ucontext_t*) cntx;
	unsigned long pc = context-> uc_mcontext.gregs[REG_RIP];
	printf("Illeagal instruction at 0x%lx value 0x%x\n", pc, *(int*) pc);
	context-> uc_mcontext.gregs[ REG_RIP] = pc+1;
}

int main () {
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGSEGV, &sa, NULL);
	printf("LEts go!\n");
	//This is somehting you hould never do!
	asm(".word 0x00000000");
	here:
	printf("Piece of cake, this call is here 0x%x ! \n", &&here);
}