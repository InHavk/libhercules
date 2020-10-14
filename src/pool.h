#ifndef __POOL_INCLUDED
#define __POOL_INCLUDED

#include <stddef.h>
#include <stdlib.h>

typedef struct event_pool {
    void* (*alloc)(struct event_pool*, size_t);
    void* (*realloc)(struct event_pool*, void*, size_t, size_t);
    void  (*free)(struct event_pool*, void*);
    void  (*force_free)(struct event_pool*, void*);
    void  (*init)(struct event_pool*, void*);
    void  (*destroy)(struct event_pool*);
    void*  pool;
} Event_pool;

void pool_init(Event_pool* pool);
void pool_destroy(Event_pool* pool);
void* event_pool_alloc(Event_pool* pool, size_t size);
void* event_pool_realloc(Event_pool* pool, void* obj, size_t size, size_t prev_size);
void  event_pool_free(Event_pool* pool, void* obj);
void  event_pool_force_free(Event_pool* pool, void* obj);
void  event_pool_init(Event_pool* pool, void* args);
void  event_pool_destroy(Event_pool* pool);

#endif