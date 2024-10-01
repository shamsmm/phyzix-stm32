#include <stdarg.h>

void printf(const char* format, ...)
{
    // initializing list pointer
    va_list ptr;
    va_start(ptr, format);

    // char array to store token
    char token[1000];
    // index of where to store the characters of str in
    // token
    int k = 0;

    // ending traversal
    va_end(ptr);
}