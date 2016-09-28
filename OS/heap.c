/*

//Heap is a thing

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
    
    char *heap = malloc(20);
    printf("the heap variable at: %p\n", &heap);

    printf("pointing to: %p\n", heap);


    char command [50];
    sprintf(command, "cat /proc/%d/maps", pid);
    system(command);
    return 0;
}
*/


/*
undefined behavior.
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char *heap = malloc(20);
    *heap = 0x61;
    printf("heap pointing to: 0x%x\n", *heap);
    free(heap);

    char *foo = malloc(20);
    *foo=0x62;

    printf("foo pointing to 0x%x\n", *foo);
    //danger head
    *heap=0x63;
    printf("or is foo pointing to 0x%x\n", *foo);
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

    long *heap = (unsigned long*) calloc(200, sizeof(unsigned));
    printf("heap[2] 0x%lx\n", heap[2]);
    printf("heap[1] 0x%lx\n", heap[1]);
    printf("heap[0] 0x%lx\n", heap[0]);
    printf("heap[-1] 0x%lx\n", heap[-1]);
    printf("heap[-2] 0x%lx\n", heap[-2]);

    free(heap);
    printf("asd heap[2] 0x%lx\n", heap[2]);
    printf("asd heap[1] 0x%lx\n", heap[1]);
    printf("asd heap[0] 0x%lx\n", heap[0]);
    printf("asd heap[-1] 0x%lx\n", heap[-1]);
    printf("asd heap[-2] 0x%lx\n", heap[-2]);

    char command [50];
    sprintf(command, "cat /proc/%d/maps", pid);
    system(command);
    return 0;
}