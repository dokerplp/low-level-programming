#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>

#include "mem.h"

void test1() {

    printf("Test-1: Started\n");

    void * allocated = _malloc(sizeof(int32_t) * 3);
    int32_t * arr = allocated;
    debug_heap(stderr, HEAP_START);
    _free(arr);
    debug_heap(stderr, HEAP_START);

    printf("Test-1: Finished Successfully\n");
}

void test2() {

    printf("Test-2: Started\n");

    int32_t** array_2d = _malloc(sizeof(int32_t *) * 5);
    debug_heap(stderr, HEAP_START);
    for (size_t i = 0; i < 5; i++) {
        array_2d[i] = _malloc(sizeof(int32_t) * 100);
        for (size_t j = 0; j < 100; j++) {
            array_2d[i][j] = i*100 + j;
        }
    }
    debug_heap(stderr, HEAP_START);
    test1();
    _free(array_2d[1]);
    debug_heap(stderr, HEAP_START);
    _free(array_2d[0]);
    debug_heap(stderr, HEAP_START);
    test1();
    for (size_t i = 2; i < 5; i++) {
        _free(array_2d[i]);
    }
    debug_heap(stderr, HEAP_START);
    _free(array_2d);
    debug_heap(stderr, HEAP_START);

    printf("Test-2: Finished Successfully\n");
}

void test3() {

    printf("Test-3: Started\n");

    void* b1 = _malloc(8000);
    debug_heap(stderr, HEAP_START);
    void* b2 = _malloc(800);
    debug_heap(stderr, HEAP_START);
    _free(b1);
    _free(b2);
    debug_heap(stderr, HEAP_START);
    void* b3 = _malloc(10000);
    debug_heap(stderr, HEAP_START);
    _free(b3);
    debug_heap(stderr, HEAP_START);

    printf("Test-3: Finished Successfully\n");
}

void test4() {

    printf("Test-4: Started\n");

    void* const b1 = _malloc(21132113);
    debug_heap(stderr, HEAP_START);
    void* const garbage = (char*) b1 + 21132113;
    map_pages(garbage, 4096, 0);
    void* const b2 = _malloc(8175);
    debug_heap(stderr, HEAP_START);
    _free(b2);
    _free(b1);
    debug_heap(stderr, HEAP_START);

    printf("Test-4: Finished Successfully\n");
}


int main() {
    test1();
    test2();
    test3();
    test4();
}
