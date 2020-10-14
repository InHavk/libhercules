#include "pool.h"

void* event_pool_alloc(Event_pool* pool, size_t size){
    return malloc(size);
}
void* event_pool_realloc(Event_pool* pool, void* obj, size_t size, size_t prev_size){
    return realloc(obj, size);
}
void  event_pool_free(Event_pool* pool, void* obj){
    free(obj);
}
void  event_pool_force_free(Event_pool* pool, void* obj){
    free(obj);
}
void  event_pool_init(struct event_pool* pool, void* args){

}
void  event_pool_destroy(struct event_pool* pool){

}
