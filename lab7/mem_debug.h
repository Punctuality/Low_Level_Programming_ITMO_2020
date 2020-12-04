//
// Created by Sergey Fedorov on 11/19/20.
//

#ifndef LOW_LEVEL_PROGRAMMING_ITMO_2020_MEM_DEBUG_H
#define LOW_LEVEL_PROGRAMMING_ITMO_2020_MEM_DEBUG_H

#include "mem.h"

#define DEBUG_FIRST_BYTES 50
#define LOG

void memalloc_debug_struct_info(FILE* f, struct mem const* const address);
void memalloc_debug_heap(FILE* f, struct mem const* ptr);

#endif //LOW_LEVEL_PROGRAMMING_ITMO_2020_MEM_DEBUG_H
