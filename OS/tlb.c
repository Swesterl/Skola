
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PAGES 32
#define PAGESIZE (32*1024)
#define REFS (1024 * 1024 * 1024)

int main (int argc, char * argv[]){
	char *memory = malloc((long) PAGESIZE * PAGES);
	for(int p = 0 ; p < PAGES ; p++){
		long ref = (long) p * PAGESIZE;
		memory[ref] += 1;
	}
	clock_t c_start, c_stop;
	struct timespec t_start, t_stop;

    printf("#TLB experiment \n" ) ;
    printf("# pagesize = %dKib\n" , (PAGESIZE/1024));
    printf("# max pages = %dKi\n" , (PAGES/1024));
    printf("# total number or references = %dMi\n" , (REFS/ (1024 * 1024)));
	printf("#pages \t proc \t wall\n");
	for(int pages = 1 ; pages <= PAGES; pages *= 2){
		int loops = REFS / pages;
		clock_gettime(CLOCK_MONOTONIC_COARSE, &t_start);
		c_start = clock();
		int m = 0 ;
		for(int l = 0 ; l < loops; l++){
			for(int p = 0 ; p < pages; p++){
				long ref = (long) p * PAGESIZE;
				memory[ref] += 1;
			}	
		}
		c_stop = clock();
		clock_gettime(CLOCK_MONOTONIC_COARSE, &t_stop);
		{
			double proc;
			long wall;
			proc = ((double)(c_stop-c_start))/CLOCKS_PER_SEC;
			wall = t_stop.tv_sec - t_start.tv_sec;
			printf("%d\t%.2f\t%ld\n", pages, proc, wall);

		}
	}
	return 0;
}