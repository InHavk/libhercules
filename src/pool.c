#include "pool.h"

void pool_init(Event_pool* pool, void* args){
    pool->alloc = &event_pool_alloc;
    pool->realloc = &event_pool_realloc;
    pool->free = &event_pool_free;
    pool->force_free = &event_pool_force_free;
    pool->init = &event_pool_init;
    pool->destroy = &event_pool_destroy;
    pool->pool = NULL;
    pool->init(pool, args);
}

void pool_destroy(Event_pool* pool){
    pool->destroy(pool);
    event_pool_force_free(pool, pool);
}