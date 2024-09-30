#include <stddef.h>
#include <cstdint>

typedef struct {
    unsigned int size: 30,
                 free: 1,
                 last: 1;
} block_header_t;

void * malloc(size_t size) {
    extern uint32_t end[];
    static block_header_t * head;

    // Initialize the heap
    if (head == nullptr) {
        head = (block_header_t *) &end;
        *head = {0, 0, 1};
    }

    block_header_t * current_header_ptr = head;

    // Find a free block
    while (!current_header_ptr->last) {
        if (current_header_ptr->free && current_header_ptr->size >= size) {
            current_header_ptr->free = 0;
            return current_header_ptr + sizeof(block_header_t);
        }

        current_header_ptr += current_header_ptr->size + sizeof(block_header_t);
    }

    // Allocate a new block
    current_header_ptr->last = 0;
    block_header_t * new_block = current_header_ptr + current_header_ptr->size + sizeof(block_header_t);

    new_block->size = size;
    new_block->free = 0;
    new_block->last = 1;

    return new_block + sizeof(block_header_t);
}

void free(void* ptr) {
    block_header_t * block = (block_header_t *) ptr - sizeof(block_header_t);
    block->free = 1;
}

void * operator new(size_t size) {
    return malloc(size);
}

void * operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}


void * operator new(size_t size, void* ptr) noexcept {
    return ptr;
}

void operator delete(void* ptr, void* place) noexcept {
}