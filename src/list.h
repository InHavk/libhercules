// MIT License (see LICENSE file)
#ifndef __LIST_INCLUDED
#define __LIST_INCLUDED
#include <stddef.h>
#include <stdlib.h>

typedef struct list_element {
    struct list_element* previous;
    struct list_element* next;
    void* value;
} List_element;

typedef struct {
    size_t size;
    List_element* el;
} List;

List* list_create();
size_t list_size(List* list);
List_element* list_get_latest(List* list);
void list_append(List* list, void* value);
void list_delete_latest(List* list);
void list_free(List* list);
#endif