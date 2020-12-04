//
// Created by Sergey Fedorov on 11/19/20.
//

#include "mem.h"

#include <sys/mman.h>

// STATIC POINTER TO THE START OF THE HEAP
static void* heap_start = NULL;

static struct mem* find_available(size_t query);
static struct mem* find_last(void);
static void  align_mem(void);

size_t threshold_size(size_t init);

void* mem_malloc(size_t query) {
    struct mem* ptr;
    struct mem* end;

    ptr = (struct mem*) find_available(query + sizeof(struct mem));

    if (ptr != NULL) {
        end = (struct mem*) (((char*) ptr) + sizeof(struct mem) + query);
        end->next = NULL;
        end->capacity = ptr->capacity - query - sizeof(struct mem);
        end->is_free = 1;

        ptr->next = end;
        ptr->capacity = query;
        ptr->is_free = 0;

        return ptr + 1;
    } else {
        size_t new_size = threshold_size(query + sizeof(struct mem));

        struct mem* last_ptr = NULL;
        if (heap_start != NULL) last_ptr = find_last();
        ptr = (struct mem*) heap_init(new_size);
        if (last_ptr != NULL) last_ptr->next = ptr;

        if ((long long) ptr->capacity - (long long) query - (long long) sizeof(struct mem) > 0) {
            end = (struct mem*) (((char*) ptr) + sizeof(struct mem) + query); // TODO Brackets
            end->next = NULL;
            end->capacity = ptr->capacity - query - sizeof(struct mem);
            end->is_free = 1;

            ptr->next = end;
        }
        ptr->capacity = query;
        ptr->is_free = 0;

        return ptr + 1;
    }
}
void mem_free(void* mem) {
    mem = (char*) mem - sizeof(struct mem);
    ((struct mem*) mem)->is_free = 1;
    align_mem(); // TODO Resolve free
}

void* heap_init(size_t initial_size) {
    struct mem* new_ptr =
            (struct mem*) mmap(HEAP_START, initial_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

    if (heap_start == NULL) heap_start = (void*) new_ptr;

    new_ptr->next = NULL;
    new_ptr->capacity = initial_size - sizeof(struct mem);
    new_ptr->is_free = 1;

    return new_ptr;
}

// HELPERS
static struct mem* find_available(size_t query) {
    struct mem* ptr = (struct mem*) heap_start;
    while (ptr) {
        if (ptr->is_free && ptr->capacity >= query)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

static struct mem* find_last(void) {
    struct mem* ptr = (struct mem*) heap_start;
    while (ptr->next != NULL) ptr = ptr->next;
    return ptr;
}

static void align_mem(void) {
    struct mem* ptr = (struct mem*) heap_start;
    while (ptr != NULL && ptr->next != NULL) {
        if (
            ptr->is_free &&
            ptr->next->is_free &&
            (struct mem*) ((char*) ptr + ptr->capacity + sizeof(struct mem)) == ptr->next
            ) {
            ptr->capacity += ptr->next->capacity + sizeof(struct mem);
            ptr->next = ptr->next->next;
        }
        ptr = ptr->next;
    }
}

size_t threshold_size(size_t init) {
    return init > MEMORY_CHUNK ? init : MEMORY_CHUNK;
}
