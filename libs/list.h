// MIT License (see LICENSE file)
#ifndef __LIST_INCLUDED
#define __LIST_INCLUDED
#include <stddef.h>
#include "pool.h"

typedef struct list_element {
    struct list_element* previous;
    struct list_element* next;
    void* value;
} List_element;

typedef struct {
    size_t size;
    List_element* el;
    List_element* latest;
} List;

List* list_create(Event_pool* pool);
size_t list_size(List* list);
List_element* list_get_latest(List* list);
void list_append(Event_pool* pool, List* list, void* value);
void list_delete_latest(Event_pool* pool, List* list);
void list_free(Event_pool* pool, List* list);
#endif