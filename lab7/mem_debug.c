//
// Created by Sergey Fedorov on 11/19/20.
//

#include "mem_debug.h"

void memalloc_debug_struct_info(FILE* f, struct mem const* const address) {

    fprintf(f, "start: %p\nsize: %lu\nis_free: %d\nnext: %p\n",
                (void*) address,
                address->capacity,
                address->is_free,
                (void*) address->next
            );

    size_t i;
    for (i = 0; i < DEBUG_FIRST_BYTES && i < address->capacity; i++)
        fprintf(f, "%hhX", ((char*) address)[sizeof(struct mem) + i]);

    putc('\n', f);
}

void memalloc_debug_heap(FILE* f, struct mem const* ptr) {
#ifdef LOG
    printf("\nStarted debugging heap with start in %p\n", (void*) ptr);
#endif
    for(; ptr; ptr = ptr->next) {
#ifdef LOG
        printf("Debugging %p\n", (void*) ptr);
#endif
        memalloc_debug_struct_info(f, ptr);
    }
}
