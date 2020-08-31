#ifndef __POOL_INCLUDED
#define __POOL_INCLUDED

#include <stddef.h>
#include <stdlib.h>

typedef struct event_pool {
    void* (*alloc)(size_t);
    void* (*realloc)(void*, size_t);
    void  (*free)(void*);
    void  (*force_free)(void*);
    void  (*init)(struct event_pool*);
    void  (*destroy)(struct event_pool*);
    void*  pool;
} Event_pool;

Event_pool* pool_init();
void pool_destroy(Event_pool* pool);
void* event_pool_alloc(size_t size);
void* event_pool_realloc(void* obj, size_t size);
void  event_pool_free(void* obj);
void  event_pool_force_free(void* obj);
void  event_pool_init(Event_pool* pool);
void  event_pool_destroy(Event_pool* pool);

#endif