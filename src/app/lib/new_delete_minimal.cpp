#include <stddef.h>

void* malloc(size_t size) {
    return NULL;
}

void free(void* ptr) {
}

void* operator new(size_t size) {
return malloc(size);  // Use malloc for memory allocation
}

// Minimal "new[]" operator (for arrays)
void* operator new[](size_t size) {
return malloc(size);  // Use malloc for memory allocation
}

// Minimal "delete" operator
void operator delete(void* ptr) noexcept {
free(ptr);  // Use free to deallocate memory
}

// Minimal "delete[]" operator (for arrays)
void operator delete[](void* ptr) noexcept {
free(ptr);  // Use free to deallocate memory
}


void* operator new(size_t size, void* ptr) noexcept {
return ptr;  // Placement new does nothing, just returns the pointer
}

void operator delete(void* ptr, void* place) noexcept {
// Placement delete does nothing
}