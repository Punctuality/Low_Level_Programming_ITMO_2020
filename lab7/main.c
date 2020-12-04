//
// Created by Sergey Fedorov on 11/19/20.
//

#include "mem.h"
#include "mem_debug.h"

#include <stdio.h>

struct movie{
    int id;
    double rating;
    char* name;
};

int main() {

    void* heap_start = NULL;

    void* big_mem_test = mem_malloc(MEMORY_CHUNK * 3);

    heap_start = (char*) big_mem_test - sizeof(struct mem);
    memalloc_debug_heap(stdout, heap_start);

    puts("^^ FIRST\n");

    struct movie * gump = mem_malloc(sizeof(struct movie));
    gump->id = 109830;
    gump->rating = 8.8;
    gump->name = "Forrest Gump";

    memalloc_debug_heap(stdout, heap_start);

    puts("^^ SECOND\n");

    struct movie * citizen_kane = mem_malloc(sizeof(struct movie));
    citizen_kane->id = 33467;
    citizen_kane->rating = 8.3;
    citizen_kane->name = "Citizen Kane";

    memalloc_debug_heap(stdout, heap_start);

    puts("^^ THIRD\n");

    struct movie * only_lovers_left_alive = mem_malloc(sizeof(struct movie));
    only_lovers_left_alive->id = 1714915;
    only_lovers_left_alive->rating = 7.3;
    only_lovers_left_alive->name = "Only Lovers Left Alive";

    memalloc_debug_heap(stdout, heap_start);

    puts("^^ FORTH (BEFORE FREE)\n");

    mem_free(only_lovers_left_alive);
    mem_free(citizen_kane);
    mem_free(gump);

    memalloc_debug_heap(stdout, heap_start);

    puts("^^ FORTH\n");
}
