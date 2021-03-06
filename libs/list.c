// MIT License (see LICENSE file)
#include "list.h"
#include <stdlib.h>

List* list_create(Event_pool* pool){
    List* list = pool->alloc(pool, sizeof(List));
    list->size = 0;
    list->el = NULL;
    list->latest = NULL;
    return list;
}

size_t list_size(List* list){
    return list->size;
}

List_element* list_get_latest(List* list){
    if(list->el == NULL){
        return NULL;
    } else {
        return list->latest;
    }
    
}

void list_append(Event_pool* pool, List* list, void* value){
    List_element* new_el = pool->alloc(pool, sizeof(List_element));
    new_el->value = value;
    new_el->next = NULL;
    List_element* latest = list_get_latest(list);
    if(latest == NULL){
        list->el = new_el;
        new_el->previous = NULL;
    } else {
        new_el->previous = latest;
        new_el->previous->next = new_el;
    }
    list->latest = new_el;
    list->size++;
}

void list_delete_latest(Event_pool* pool, List* list){
    if(list->size > 0){
        List_element* latest = list_get_latest(list);
        pool->free(pool, latest->value);
        if(latest->previous != NULL){
            latest->previous->next = NULL;
            list->latest = latest->previous;
        }
        list->size--;
        pool->free(pool, latest);
        if(list->size == 0){
            list->el = NULL;
        }
    }
}

void list_free(Event_pool* pool, List* list){
    List_element* latest = list_get_latest(list);
    List_element* previous_element;
    while(list->size > 0){
        pool->free(pool, latest->value);
        previous_element = latest->previous;
        pool->free(pool, latest);
        latest = previous_element;
        list->size--;
    }
    pool->free(pool, list);
}