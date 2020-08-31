// MIT License (see LICENSE file)
#include "list.h"
#include <stdlib.h>

List* list_create(Event_pool* pool){
    List* list = pool->alloc(sizeof(List));
    list->size = 0;
    list->el = NULL;
    return list;
}

size_t list_size(List* list){
    return list->size;
}

List_element* list_get_latest(List* list){
    if(list->el == NULL){
        return NULL;
    } else {
        List_element* element = list->el;
        while(element->next != NULL){
            element = element->next;
        }
        return element;
    }
    
}

void list_append(Event_pool* pool, List* list, void* value){
    List_element* new_el = pool->alloc(sizeof(List_element));
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
    list->size++;
}

void list_delete_latest(Event_pool* pool, List* list){
    if(list->size > 0){
        List_element* latest = list_get_latest(list);
        pool->free(latest->value);
        if(latest->previous != NULL){
            latest->previous->next = NULL;
        }
        list->size--;
        pool->free(latest);
        if(list->size == 0){
            list->el = NULL;
        }
    }
}

void list_free(Event_pool* pool, List* list){
    List_element* latest = list_get_latest(list);
    List_element* previous_element;
    while(list->size > 0){
        pool->free(latest->value);
        previous_element = latest->previous;
        pool->free(latest);
        latest = previous_element;
        list->size--;
    }
    pool->free(list);
}