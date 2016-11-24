/*
int s i m u l a t e ( int ∗ seq , p t e ∗ t a b l e , int r e f s , int frms , int pgs ) {
int h i t s = 0 ;
int a l l o c a t e d = 0 ;
int i ;
f o r ( i = 0 ; i < r e f s ; i ++) {
int next = s e q [ i ] ;
p t e ∗ e n t r y = &t a b l e [ next ] ;
i f ( entry −>p r e s e n t == 1 ) {
h i t s ++;
} else {
i f ( a l l o c a t e d < frms ) {
a l l o c a t e d ++;
4entry −>p r e s e n t = 1 ;
} else {
pte ∗ e v i c t ;
do {
int rnd = rand ()% pgs ;
e v i c t = &t a b l e [ rnd ] ;
} while ( e v i c t −>p r e s e n t != 1 ) ;
e v i c t −>p r e s e n t = 0 ;
entry −>p r e s e n t = 1 ;
}
}
}
return h i t s ;
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#define HIGH 20
#define FREQ 80
#define SAMPLES 20
typedef struct pte
{
	int id;
	int present;
	struct pte *next;
	struct pte *prev;
} pte;

int simulate(int * seq, pte * table, int refs, int frms, int pgs){
	int hits = 0;
	int allocated = 0;
	pte *first = NULL;
	pte *last = NULL;


	int i;
	for(i = 0 ; i < refs ;  i++){
		int next = seq[i];
		pte *entry = &table[next];
		if(entry -> present == 1){
			hits++;
			//u n l i n k e n t r y and p l a c e l a s t 
			first = entry -> prev;
			entry -> prev -> next = NULL;
			entry -> prev = NULL;
			entry -> next = last;
			last = entry;

		} else {
			if(allocated < frms) {
			allocated++;
			entry -> present = 1;
			entry ->prev = last;
			entry ->next = NULL;
			// p l a c e e n t r y l a s 
			entry -> next = last;
			last = entry;
			} else {
				pte *evict;
				evict = first;
				first = evict -> next;
				evict -> present = 0;
				entry -> present = 1;
				entry -> prev = last;
				entry -> next = NULL;
				//p l a c e e n t r y l a s t 
				entry -> next = last;
				last = entry;
			}
		}
	}
	return hits;
}

void cleartable (pte * table, int pages){
	for(int i = 0 ; i < pages ; i++){
		table[i].present = 0;
	}
}

void init (int * sequence, int refs, int pages){
	int high = (int) (pages * ((float)HIGH/ 100));
	for(int i = 0 ; i < refs ; i++) { 
			if(rand()%100 < FREQ){
				sequence[i] = rand() % high;
			} else {
				sequence[i] = high + rand() % (pages - high);
			}
		}
}

int main (int argc, char * argv[]) {
	
	srand(time(NULL));
	int refs = 100000;
	int pages = 100;
	//pte table [PAGES];
	pte * table = (pte*) malloc (pages * sizeof(pte));
	int * sequence = (int *) malloc (refs * sizeof(int));
	init(sequence, refs, pages);
	/*
	for(int i = 0; i < refs ; i++) {
		printf(", %d", sequence[i]);
	} 
	*/
	printf("\n");


	printf("#this is a benchmark of random rplacement \n");
	printf("# %d page references\n", refs);
	printf("# %d pages\n", pages);
	printf("#\n#\n# frames\tratio\n");
	int frames;
	int incr = pages/SAMPLES;
	for(frames = incr ; frames <= pages ; frames += incr){
		cleartable(table, pages);
		int hits = simulate(sequence, table, refs, frames, pages);
		float ratio = (float) hits / refs;
		printf("%d\t%.2f\n", frames, ratio);
	}

	return 0; 

}
