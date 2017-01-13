#pragma once
#include <stdlib.h>
typedef struct kmem_cache_s kmem_cache_t;
#define BLOCK_SIZE 4096
#define CACHE_L1_LINE_SIZE 64

void kmem_init(void *space, int block_num); 
/*
Initializes the allocator
space is the  pointer to the start of memory space
block_num is number of blocks in the allocator
*/
kmem_cache_t *kmem_cache_create(const char *name, size_t size, void(*ctor)(void *), void(*dtor)(void *)); 
/* 
Allocates cache
name is human readable name of cache
size is the size of objects in cache
ctor is the constructor function, can be NULL
dtor is the destructor function, can be NULL
Returns pointer to cache struct
*/
int kmem_cache_shrink(kmem_cache_t *cachep); 
/* 
Shrink cache
cachep is the pointer to the cache that should be shrunk
Lets go of all the slabs in slabs_free list
Returns number of blocks freed
*/
void *kmem_cache_alloc(kmem_cache_t *cachep); 
/* 
Allocate one object from cache
This will automaticly grow cache if there's no room
*/
void kmem_cache_free(kmem_cache_t *cachep, void *objp); 
/* 
Deallocate object objectp from cache cachep
Update slabs lists as needed
*/
void *kmalloc(size_t size); 
/* 
Alloacate one small memory buffer 
Memory buffer size can range from 2^5 to 2^17
Best to have a static array of caches for this!
*/
void kfree(const void *objp); 
/*
Deallocate one small memory buffer
objp is the buffer to dealloc
*/
void kmem_cache_destroy(kmem_cache_t *cachep); // Deallocate cache BRUTALLY!
void kmem_cache_info(kmem_cache_t *cachep); 
/* 
Print cache info
Should print cache name, size of data in bytes, size of cache in blocks, num of slabs, num of objects in a slab, utilization in %
*/
int kmem_cache_error(kmem_cache_t *cachep); 
/*
Print error message
Returns 0 if no errors, returns non 0 value if error
*/