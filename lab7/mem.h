//
// Created by Sergey Fedorov on 11/19/20.
//

#ifndef LOW_LEVEL_PROGRAMMING_ITMO_2020_MEM_H
#define LOW_LEVEL_PROGRAMMING_ITMO_2020_MEM_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define HEAP_START ((void*) 0x04040000)
#define MEMORY_CHUNK 4 * 1024 * 1024 // 4Kb

struct mem;

#pragma pack(push, 1)
struct mem {
    struct mem* next;
    size_t capacity;
    char is_free;
};
#pragma pack(pop)

void* mem_malloc(size_t query);
void  mem_free(void* mem);
void* heap_init(size_t initial_size);

#endif //LOW_LEVEL_PROGRAMMING_ITMO_2020_MEM_H
