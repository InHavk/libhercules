#include "libhercules.h"
#include <time.h>
#include <string.h>


void generate_uuid_v4(uint8_t* uuid) {
    uuid[0] = rand() % 256;
    uuid[1] = rand() % 256;
    uuid[2] = rand() % 256;
    uuid[3] = rand() % 256;
    uuid[4] = rand() % 256;
    uuid[5] = rand() % 256;
    uuid[6] = ((rand() % 256) & 0x0F) | 0x40;
    uuid[7] = rand() % 256;
    uuid[8] = ((rand() % 256) & 0x3F) | 0x80;
    uuid[9] = rand() % 256;
    uuid[10] = rand() % 256;
    uuid[11] = rand() % 256;
    uuid[12] = rand() % 256;
    uuid[13] = rand() % 256;
    uuid[14] = rand() % 256;
    uuid[15] = rand() % 256;
}

uint64_t generate_current_timestamp() {
    struct timespec* t = malloc(sizeof(struct timespec));
    clock_gettime(CLOCK_REALTIME, t);
    uint64_t timestamp = (t->tv_sec * 10000000) + (t->tv_nsec / 100);
    free(t);
    return timestamp;
}

Event* event_create(uint8_t version, uint64_t timestamp, uint8_t* uuid) {
    Event* event = malloc(sizeof(Event));
    event->payload = list_create();
    event->version = version;
    event->timestamp = timestamp;
    memcpy(event->UUID, uuid, 16);
    return event;
}

void event_free(Event* event){
    //list_free(event->payload);
    container_free(event->payload);
    free(event);
}

void container_free(List* container){
    List_element* top_el = container->el;
    List_element* last;
    while(top_el != NULL){
        Tag* tag = (Tag*) top_el->value;
        if(tag->datatype == BYTE){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == SHORT){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == INTEGER){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == LONG){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == FLAG){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == FLOAT){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == DOUBLE){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == STRING){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == UUID){
            free(tag->value);
            goto next_tag;
        }
        if(tag->datatype == NULL_TYPE){
            goto next_tag;
        }
        if(tag->datatype == VECTOR){
            vector_free(tag_get_Vector(tag));
            goto next_tag;
        }
        if(tag->datatype == CONTAINER){
            container_free(tag_get_Container(tag));
            goto next_tag;
        }
        next_tag: last = top_el;
        top_el = top_el->next;
        free(last);
    }
    free(container);
}

void vector_free(Vector* vector){
    List_element* top_el = vector->values->el;
    List_element* last;
    while(top_el != NULL){
        if(vector->datatype == BYTE){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == SHORT){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == INTEGER){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == LONG){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == FLAG){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == FLOAT){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == DOUBLE){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == STRING){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == UUID){
            free(top_el->value);
            goto next_tag;
        }
        if(vector->datatype == NULL_TYPE){
            goto next_tag;
        }
        if(vector->datatype == VECTOR){
            vector_free(tag_get_Vector(top_el));
            goto next_tag;
        }
        if(vector->datatype == CONTAINER){
            container_free(tag_get_Container(top_el));
            goto next_tag;
        }
        next_tag: last = top_el;
        top_el = top_el->next;
        free(last);
    }
    free(vector);
}

Event* create_event() {
    uint8_t* uuid = malloc(sizeof(uint8_t) * 16);
    generate_uuid_v4(uuid);
    Event* event = event_create(0x01, generate_current_timestamp(), uuid);
    free(uuid);
    return event;
}

Tag* container_find_tag(List* list, int8_t key_length, char* key_name){
    if(list->size > 0){
        List_element* element = list->el;
        for(uint8_t i = 0; i < list->size; ++i){
            Tag* tag = (Tag*) element->value;
            if(tag->key.length == key_length && strcmp(key_name, tag->key.value) == 0){
                return tag;
            }
            element = element->next;
        }
        return NULL;
    } else {
        return NULL;
    }
}

void container_add_tag_Byte(List* list, int8_t key_length, char* key_name, uint8_t value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = BYTE;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(uint8_t));
    *((uint8_t*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_Short(List* list, int8_t key_length, char* key_name, int16_t value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = SHORT;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(int16_t));
    *((int16_t*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_Integer(List* list, int8_t key_length, char* key_name, int32_t value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = INTEGER;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(int32_t));
    *((int32_t*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_Long(List* list, int8_t key_length, char* key_name, int64_t value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = LONG;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(int64_t));
    *((int64_t*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_Flag(List* list, int8_t key_length, char* key_name, char value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = FLAG;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(char));
    *((char*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_Float(List* list, int8_t key_length, char* key_name, float value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = FLOAT;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(float));
    *((float*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_Double(List* list, int8_t key_length, char* key_name, double value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = DOUBLE;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(double));
    *((double*) tag->value) = value;
    list_append(list, tag);
}

void container_add_tag_String(List* list, int8_t key_length, char* key_name, char* value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = STRING;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    uint64_t size_of_value = strlen(value);
    tag->value = malloc(sizeof(char) * (size_of_value + 1));
    strcpy(tag->value, value);
    list_append(list, tag);
}

void container_add_tag_UUID(List* list, int8_t key_length, char* key_name, uint8_t* value){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = UUID;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(uint8_t) * 16);
    memcpy((uint8_t*) tag->value, value, 16);
    list_append(list, tag);
}

void container_add_tag_Null(List* list, int8_t key_length, char* key_name){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = NULL_TYPE;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(void));
    list_append(list, tag);
}

void container_add_tag_Vector(List* list, enum DataType datatype, int8_t key_length, char* key_name){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = VECTOR;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = malloc(sizeof(Vector));
    ((Vector*) tag->value)->datatype = datatype;
    ((Vector*) tag->value)->values = list_create();
    list_append(list, tag);
}

void container_add_tag_Container(List* list, int8_t key_length, char* key_name){
    Tag* tag = malloc(sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = CONTAINER;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = list_create();
    list_append(list, tag);
}

char* event_to_bin(Event* event, size_t* binary_size){
    size_t* binary_max_size = malloc(sizeof(size_t));
    *binary_max_size = 1024 * 4;
    char* binary_string = malloc(sizeof(char) * *binary_max_size);
    *binary_size = 0;
    // Version
    pack_be_uint8(event->version, binary_string, binary_size, binary_max_size);
    // Timestamp
    uint64_t be_timestamp = htobe64(event->timestamp);
    pack_be_uint64(be_timestamp, binary_string, binary_size, binary_max_size);
    // UUID
    pack_be_uint8_array(event->UUID, 16, binary_string, binary_size, binary_max_size);
    // Payload
    // Container
    binary_string = container_to_bin(event->payload, binary_string, binary_size, binary_max_size);
    return binary_string;
}

char* container_to_bin(List* container, char* binary_string, size_t* binary_size, size_t* binary_max_size){
    uint16_t be_length = htobe16(container->size);
    pack_be_uint16(be_length, binary_string, binary_size, binary_max_size);
    List_element* top_el = container->el;
    while(top_el != NULL){
        Tag* tag = (Tag*) top_el->value;
        // Key
        // KeyLength
        pack_be_uint8(tag->key.length, binary_string, binary_size, binary_max_size);
        // KeyValue
        pack_be_uint8_array(tag->key.value, tag->key.length, binary_string, binary_size, binary_max_size);
        // Datatype
        pack_be_uint8(tag->datatype, binary_string, binary_size, binary_max_size);
        // Value
        if(tag->datatype == BYTE){
            pack_be_uint8(tag_get_Byte(tag), binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == SHORT){
            int16_t be_short = htobe16(tag_get_Short(tag));
            pack_be_uint16(be_short, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == INTEGER){
            int32_t be_integer = htobe32(tag_get_Integer(tag));
            pack_be_uint32(be_integer, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == LONG){
            int64_t be_long = htobe64(tag_get_Long(tag));
            pack_be_uint64(be_long, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == FLAG){
            uint8_t be_flag = tag_get_Flag(tag);
            pack_be_uint8(be_flag, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == FLOAT){
            uint32_t be_float = htobe32(tag_get_Float(tag));
            pack_be_uint64(be_float, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == DOUBLE){
            uint64_t be_double = htobe64(tag_get_Double(tag));
            pack_be_uint64(be_double, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == STRING){
            int32_t string_size = strlen(tag_get_String(tag));
            int32_t be_string_size = htobe32(string_size);
            pack_be_uint32(be_string_size, binary_string, binary_size, binary_max_size);
            pack_be_uint8_array(tag_get_String(tag), string_size, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == UUID){
            pack_be_uint8_array(tag_get_UUID(tag), 16, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == NULL_TYPE){
            goto next_tag;
        }
        if(tag->datatype == VECTOR){
            Vector* vector = tag_get_Vector(tag);
            pack_be_uint8(vector->datatype, binary_string, binary_size, binary_max_size);
            binary_string = vector_to_bin(vector, binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        if(tag->datatype == CONTAINER){
            binary_string = container_to_bin(tag_get_Container(tag), binary_string, binary_size, binary_max_size);
            goto next_tag;
        }
        next_tag: top_el = top_el->next;
    }
    return binary_string;
}

char* vector_to_bin(Vector* vector, char* binary_string, size_t* binary_size, size_t* binary_max_size){
    int32_t be_length = htobe32(vector->values->size);
    pack_be_uint32(be_length, binary_string, binary_size, binary_max_size);
    List_element* el = vector->values->el;
    while(el != NULL){
        if(vector->datatype == BYTE){
            pack_be_uint8(tag_get_Byte(el), binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == SHORT){
            int16_t be_short = htobe16(tag_get_Short(el));
            pack_be_uint16(be_short, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == INTEGER){
            int32_t be_integer = htobe32(tag_get_Integer(el));
            pack_be_uint32(be_integer, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == LONG){
            int64_t be_long = htobe64(tag_get_Long(el));
            pack_be_uint64(be_long, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == FLAG){
            char flag = tag_get_Flag(el);
            pack_be_uint8(flag, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == FLOAT){
            uint32_t be_float = htobe32(tag_get_Float(el));
            pack_be_uint32(be_float, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == DOUBLE){
            uint64_t be_double = htobe64(tag_get_Double(el));
            pack_be_uint64(be_double, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == STRING){
            int32_t string_size = strlen(tag_get_String(el));
            int32_t be_string_size = htobe32(string_size);
            pack_be_uint32(be_string_size, binary_string, binary_size, binary_max_size);
            pack_be_uint8_array(tag_get_String(el), string_size, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == UUID){
            pack_be_uint8_array(tag_get_UUID(el), 16, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == NULL_TYPE){
            goto next_el;
        }
        if(vector->datatype == VECTOR){
            Vector* be_vector = tag_get_Vector(el);
            pack_be_uint8(be_vector->datatype, binary_string, binary_size, binary_max_size);
            binary_string = vector_to_bin(be_vector, binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        if(vector->datatype == CONTAINER){
            binary_string = container_to_bin(tag_get_Container(el), binary_string, binary_size, binary_max_size);
            goto next_el;
        }
        next_el: el = el->next;
    }
    return binary_string;
}

void vector_add_Byte(Vector* vector, uint8_t value){
    uint8_t* v_byte = malloc(sizeof(uint8_t));
    *v_byte = value;
    list_append(vector->values, v_byte);
}

void vector_add_Short(Vector* vector, int16_t value){
    int16_t* v_short = malloc(sizeof(int16_t));
    *v_short = value;
    list_append(vector->values, v_short);
}

void vector_add_Integer(Vector* vector, int32_t value){
    int32_t* v_integer = malloc(sizeof(int32_t));
    *v_integer = value;
    list_append(vector->values, v_integer);
}

void vector_add_Long(Vector* vector, int64_t value){
    int64_t* v_long = malloc(sizeof(int64_t));
    *v_long = value;
    list_append(vector->values, v_long);
}

void vector_add_Flag(Vector* vector, char value){
    char* v_flag = malloc(sizeof(char));
    *v_flag = value;
    list_append(vector->values, v_flag);
}

void vector_add_Float(Vector* vector, float value){
    float* v_float = malloc(sizeof(float));
    *v_float = value;
    list_append(vector->values, v_float);
}

void vector_add_Double(Vector* vector, double value){
    double* v_double = malloc(sizeof(double));
    *v_double = value;
    list_append(vector->values, v_double);
}

void vector_add_String(Vector* vector, char* value){
    char* v_string = malloc(sizeof(char) * strlen(value));
    strcpy(v_string, value);
    list_append(vector->values, v_string);
}

void vector_add_UUID(Vector* vector, uint8_t* value){
    uint8_t* v_uuid = malloc(sizeof(uint8_t) * 16);
    memcpy(v_uuid, value, 16);
    list_append(vector->values, v_uuid);
}

void vector_add_Vector(Vector* vector, enum DataType datatype){
    Vector* v_vector = malloc(sizeof(Vector));
    v_vector->datatype = datatype;
    v_vector->values = list_create();
    list_append(vector->values, v_vector);
}

void vector_add_Container(Vector* vector){
    List* v_container = list_create();
    list_append(vector->values, v_container);
}