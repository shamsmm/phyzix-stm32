#include <stddef.h>
#include <cstdint>

// TODO: move into porting folder, to be platform independent

/**
 * @struct Heap_Block_Header_t
 * @brief Header for each allocated/free block in the heap
 * @var size the amount free allocated in heap memory in bytes
 * @var free 1 if block is free, 0 if block is allocated
 * @var last 1 if this is the last block in the heap, 0 otherwise
 */
typedef struct {
    unsigned int size: 30, // size in bytes
                 free: 1,
                 last: 1;
} Heap_Block_Header_t;

[[maybe_unused]] extern uint32_t end[];
static uint8_t * heap_start;

void malloc_init() {
    heap_start = (uint8_t *) &end;

    auto * header = (Heap_Block_Header_t *) heap_start;
    header->size = 0;
    header->free = 0;
    header->last = 1;
}

/// Total used memory, including possible fragmented free memory
unsigned int peak_memory() {
    auto * current_heap_ptr = (uint8_t *) &end;

    while (!((Heap_Block_Header_t *) current_heap_ptr)->last) {
        current_heap_ptr += sizeof(Heap_Block_Header_t) + ((Heap_Block_Header_t *) current_heap_ptr)->size;
    }

    return current_heap_ptr - heap_start + sizeof(Heap_Block_Header_t) + ((Heap_Block_Header_t *) current_heap_ptr)->size;
}

void * malloc(size_t size) {
    // Initialize the heap
    if (heap_start == nullptr) {
        malloc_init();
    }

    auto * current_heap_ptr = (uint8_t *) &end;

    // Find a free block
    while (!((Heap_Block_Header_t *) current_heap_ptr)->last) {
        if (((Heap_Block_Header_t *) current_heap_ptr)->free && ((Heap_Block_Header_t *) current_heap_ptr)->size >= size) {
            ((Heap_Block_Header_t *) current_heap_ptr)->free = 0;
            return current_heap_ptr + sizeof(Heap_Block_Header_t);
        }

        current_heap_ptr += sizeof(Heap_Block_Header_t) + ((Heap_Block_Header_t *) current_heap_ptr)->size;
    }

    // change last block to not be last
    ((Heap_Block_Header_t *) current_heap_ptr)->last = 0;

    // increment current heap pointer to new space
        current_heap_ptr += sizeof(Heap_Block_Header_t) + ((Heap_Block_Header_t *) current_heap_ptr)->size;

    // Allocate a new block
    auto * new_block = (Heap_Block_Header_t *) current_heap_ptr;
    new_block->size = size;
    new_block->free = 0;
    new_block->last = 1;

    return current_heap_ptr + sizeof(Heap_Block_Header_t);
}

void free(void* ptr) {
    auto block = (Heap_Block_Header_t *)((uint8_t *) ptr - sizeof(Heap_Block_Header_t));
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