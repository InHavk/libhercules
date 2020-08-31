#include "pool.h"

void* event_pool_alloc(size_t size){
    return malloc(size);
}
void* event_pool_realloc(void* obj, size_t size){
    return realloc(obj, size);
}
void  event_pool_free(void* obj){
    free(obj);
}
void  event_pool_force_free(void* obj){
    free(obj);
}
void  event_pool_init(struct event_pool* pool){

}
void  event_pool_destroy(struct event_pool* pool){

}
