//
// Created by shams on 10/1/24.
//

#ifndef PHYZIX_MALLOC_H
#define PHYZIX_MALLOC_H

void malloc_init();
void * malloc(std::size_t size);
void free(void* ptr);
unsigned int peak_memory();

#endif //PHYZIX_MALLOC_H
