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
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    uint64_t timestamp = (t.tv_sec * 10000000) + (t.tv_nsec / 100);
    return timestamp;
}

Event* event_create(Event_pool* pool, uint8_t version, uint64_t timestamp, uint8_t* uuid) {
    Event* event = pool->alloc(pool, sizeof(Event));
    event->pool = pool;
    event->payload = list_create(pool);
    event->version = version;
    event->timestamp = timestamp;
    memcpy(event->UUID, uuid, 16);
    return event;
}

void event_free(Event* event){
    container_free(event->pool, event->payload);
    event->pool->free(event->pool, event);
}

void container_free(Event_pool* pool, List* container){
    List_element* top_el = container->el;
    List_element* last;
    while(top_el != NULL){
        Tag* tag = (Tag*) top_el->value;
        switch(tag->datatype) {
            case BYTE:
            case SHORT:
            case INTEGER:
            case LONG:
            case FLAG:
            case FLOAT:
            case DOUBLE:
            case STRING:
            case UUID:
                pool->free(pool, tag->value);
                break;
            case VECTOR:
                vector_free(pool, tag_get_Vector(tag));
                break;
            case CONTAINER:
                container_free(pool, tag_get_Container(tag));
                break;
            default:
                break;
        }
        last = top_el;
        top_el = top_el->next;
        pool->free(pool, tag);
        pool->free(pool, last);
    }
    pool->free(pool, container);
}

void vector_free(Event_pool* pool, Vector* vector){
    List_element* top_el = vector->values->el;
    List_element* last;
    while(top_el != NULL){
        switch(vector->datatype){
            case BYTE:
            case SHORT:
            case INTEGER:
            case LONG:
            case FLAG:
            case FLOAT:
            case DOUBLE:
            case STRING:
            case UUID:
                pool->free(pool, top_el->value);
                break;
            case VECTOR:
                vector_free(pool, tag_get_Vector(top_el));
                break;
            case CONTAINER:
                container_free(pool, tag_get_Container(top_el));
                break;
            default:
                break;
        }
        last = top_el;
        top_el = top_el->next;
        pool->free(pool, last);
    }
    pool->free(pool, vector->values);
    pool->free(pool, vector);
}

Event* create_event(Event_pool* pool) {
    uint8_t  uuid[16];
    generate_uuid_v4(uuid);
    Event* event = event_create(pool, 0x01, generate_current_timestamp(), uuid);
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

Tag* container_add_tag_Byte(Event_pool* pool, List* list, int8_t key_length, char* key_name, uint8_t value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = BYTE;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(uint8_t));
    *((uint8_t*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Short(Event_pool* pool, List* list, int8_t key_length, char* key_name, int16_t value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = SHORT;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(int16_t));
    *((int16_t*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Integer(Event_pool* pool, List* list, int8_t key_length, char* key_name, int32_t value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = INTEGER;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(int32_t));
    *((int32_t*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Long(Event_pool* pool, List* list, int8_t key_length, char* key_name, int64_t value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = LONG;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(int64_t));
    *((int64_t*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Flag(Event_pool* pool, List* list, int8_t key_length, char* key_name, char value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = FLAG;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(char));
    *((char*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Float(Event_pool* pool, List* list, int8_t key_length, char* key_name, float value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = FLOAT;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(float));
    *((float*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Double(Event_pool* pool, List* list, int8_t key_length, char* key_name, double value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = DOUBLE;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(double));
    *((double*) tag->value) = value;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_String(Event_pool* pool, List* list, int8_t key_length, char* key_name, char* value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = STRING;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    uint64_t size_of_value = strlen(value);
    tag->value = pool->alloc(pool, sizeof(char) * (size_of_value + 1));
    strcpy(tag->value, value);
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_UUID(Event_pool* pool, List* list, int8_t key_length, char* key_name, uint8_t* value){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = UUID;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(uint8_t) * 16);
    memcpy((uint8_t*) tag->value, value, 16);
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Null(Event_pool* pool, List* list, int8_t key_length, char* key_name){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = NULL_TYPE;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = NULL;
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Vector(Event_pool* pool, List* list, enum DataType datatype, int8_t key_length, char* key_name){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = VECTOR;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = pool->alloc(pool, sizeof(Vector));
    ((Vector*) tag->value)->datatype = datatype;
    ((Vector*) tag->value)->values = list_create(pool);
    list_append(pool, list, tag);
    return tag;
}

Tag* container_add_tag_Container(Event_pool* pool, List* list, int8_t key_length, char* key_name){
    Tag* tag = pool->alloc(pool, sizeof(Tag) + (sizeof(char) * (key_length + 1)));
    tag->datatype = CONTAINER;
    tag->key.length = key_length;
    strcpy(tag->key.value, key_name);
    tag->value = list_create(pool);
    list_append(pool, list, tag);
    return tag;
}

Event_binary* event_to_bin(Event* event){
    size_t* binary_max_size = event->pool->alloc(event->pool, sizeof(size_t));
    *binary_max_size = 1024 * 8;
    Event_binary* event_binary = event->pool->alloc(event->pool, sizeof(Event_binary) + (sizeof(char) * *binary_max_size));
    event_binary->size = 0;

    // Version
    pack_be_uint8(event->pool, event->version, event_binary, binary_max_size);
    // Timestamp
    uint64_t be_timestamp = htobe64(event->timestamp);
    pack_be_uint64(event->pool, be_timestamp, event_binary, binary_max_size);
    // UUID
    pack_be_uint8_array(event->pool, event->UUID, 16, event_binary, binary_max_size);
    // Payload
    // Container
    event_binary = container_to_bin(event->pool, event->payload, event_binary, binary_max_size);
    event->pool->free(event->pool, binary_max_size);
    return event_binary;
}

Event_binary* container_to_bin(Event_pool* pool, List* container, Event_binary* event_binary, size_t* binary_max_size){
    uint16_t be_length = htobe16(container->size);
    pack_be_uint16(pool, be_length, event_binary, binary_max_size);
    List_element* top_el = container->el;
    while(top_el != NULL){
        Tag* tag = (Tag*) top_el->value;
        // Key
        // KeyLength
        pack_be_uint8(pool, tag->key.length, event_binary, binary_max_size);
        // KeyValue
        pack_be_uint8_array(pool, tag->key.value, tag->key.length, event_binary, binary_max_size);
        // Datatype
        pack_be_uint8(pool, tag->datatype, event_binary, binary_max_size);
        // Value
        int16_t be_short;
        int32_t be_integer;
        int64_t be_long;
        uint8_t be_flag;
        uint32_t be_float;
        uint64_t be_double;
        int32_t string_size;
        int32_t be_string_size;
        Vector* vector;
        switch(tag->datatype){
            case BYTE:
                pack_be_uint8(pool, tag_get_Byte(tag), event_binary, binary_max_size);
                break;
            case SHORT:
                be_short = htobe16(tag_get_Short(tag));
                pack_be_uint16(pool, be_short, event_binary, binary_max_size);
                break;
            case INTEGER:
                be_integer = htobe32(tag_get_Integer(tag));
                pack_be_uint32(pool, be_integer, event_binary, binary_max_size);
                break;
            case LONG:
                be_long = htobe64(tag_get_Long(tag));
                pack_be_uint64(pool, be_long, event_binary, binary_max_size);
                break;
            case FLAG:
                be_flag = tag_get_Flag(tag);
                pack_be_uint8(pool, be_flag, event_binary, binary_max_size);
                break;
            case FLOAT:
                be_float = htobe32(tag_get_Float(tag));
                pack_be_uint64(pool, be_float, event_binary, binary_max_size);
                break;
            case DOUBLE:
                be_double = htobe64(tag_get_Double(tag));
                pack_be_uint64(pool, be_double, event_binary, binary_max_size);
                break;
            case STRING:
                string_size = strlen(tag_get_String(tag));
                be_string_size = htobe32(string_size);
                pack_be_uint32(pool, be_string_size, event_binary, binary_max_size);
                pack_be_uint8_array(pool, tag_get_String(tag), string_size, event_binary, binary_max_size);
                break;
            case UUID:
                pack_be_uint8_array(pool, tag_get_UUID(tag), 16, event_binary, binary_max_size);
                break;
            case VECTOR:
                vector = tag_get_Vector(tag);
                pack_be_uint8(pool, vector->datatype, event_binary, binary_max_size);
                event_binary = vector_to_bin(pool, vector, event_binary, binary_max_size);
                break;
            case CONTAINER:
                event_binary = container_to_bin(pool, tag_get_Container(tag), event_binary, binary_max_size);
                break;
            default:
                break;
        }
        top_el = top_el->next;
    }
    return event_binary;
}

Event_binary* vector_to_bin(Event_pool* pool, Vector* vector, Event_binary* event_binary, size_t* binary_max_size){
    int32_t be_length = htobe32(vector->values->size);
    pack_be_uint32(pool, be_length, event_binary, binary_max_size);
    List_element* el = vector->values->el;
    while(el != NULL){
        int16_t be_short;
        int32_t be_integer;
        int64_t be_long;
        char flag;
        uint32_t be_float;
        uint64_t be_double;
        int32_t string_size;
        int32_t be_string_size;
        Vector* be_vector;
        switch(vector->datatype){
            case BYTE:
                pack_be_uint8(pool, tag_get_Byte(el), event_binary, binary_max_size);
                break;
            case SHORT:
                be_short = htobe16(tag_get_Short(el));
                pack_be_uint16(pool, be_short, event_binary, binary_max_size);
                break;
            case INTEGER:
                be_integer = htobe32(tag_get_Integer(el));
                pack_be_uint32(pool, be_integer, event_binary, binary_max_size);
                break;
            case LONG:
                be_long = htobe64(tag_get_Long(el));
                pack_be_uint64(pool, be_long, event_binary, binary_max_size);
                break;
            case FLAG:
                flag = tag_get_Flag(el);
                pack_be_uint8(pool, flag, event_binary, binary_max_size);
                break;
            case FLOAT:
                be_float = htobe32(tag_get_Float(el));
                pack_be_uint32(pool, be_float, event_binary, binary_max_size);
                break;
            case DOUBLE:
                be_double = htobe64(tag_get_Double(el));
                pack_be_uint64(pool, be_double, event_binary, binary_max_size);
                break;
            case STRING:
                string_size = strlen(tag_get_String(el));
                be_string_size = htobe32(string_size);
                pack_be_uint32(pool, be_string_size, event_binary, binary_max_size);
                pack_be_uint8_array(pool, tag_get_String(el), string_size, event_binary, binary_max_size);
                break;
            case UUID:
                pack_be_uint8_array(pool, tag_get_UUID(el), 16, event_binary, binary_max_size);
                break;
            case VECTOR:
                be_vector = tag_get_Vector(el);
                pack_be_uint8(pool, be_vector->datatype, event_binary, binary_max_size);
                event_binary = vector_to_bin(pool, be_vector, event_binary, binary_max_size);
                break;
            case CONTAINER:
                event_binary = container_to_bin(pool, tag_get_Container(el), event_binary, binary_max_size);
                break;
            default:
                break;
        }
        el = el->next;
    }
    return event_binary;
}

void vector_add_Byte(Event_pool* pool, Vector* vector, uint8_t value){
    uint8_t* v_byte = pool->alloc(pool, sizeof(uint8_t));
    *v_byte = value;
    list_append(pool, vector->values, v_byte);
}

void vector_add_Short(Event_pool* pool, Vector* vector, int16_t value){
    int16_t* v_short = pool->alloc(pool, sizeof(int16_t));
    *v_short = value;
    list_append(pool, vector->values, v_short);
}

void vector_add_Integer(Event_pool* pool, Vector* vector, int32_t value){
    int32_t* v_integer = pool->alloc(pool, sizeof(int32_t));
    *v_integer = value;
    list_append(pool, vector->values, v_integer);
}

void vector_add_Long(Event_pool* pool, Vector* vector, int64_t value){
    int64_t* v_long = pool->alloc(pool, sizeof(int64_t));
    *v_long = value;
    list_append(pool, vector->values, v_long);
}

void vector_add_Flag(Event_pool* pool, Vector* vector, char value){
    char* v_flag = pool->alloc(pool, sizeof(char));
    *v_flag = value;
    list_append(pool, vector->values, v_flag);
}

void vector_add_Float(Event_pool* pool, Vector* vector, float value){
    float* v_float = pool->alloc(pool, sizeof(float));
    *v_float = value;
    list_append(pool, vector->values, v_float);
}

void vector_add_Double(Event_pool* pool, Vector* vector, double value){
    double* v_double = pool->alloc(pool, sizeof(double));
    *v_double = value;
    list_append(pool, vector->values, v_double);
}

void vector_add_String(Event_pool* pool, Vector* vector, char* value){
    char* v_string = pool->alloc(pool, sizeof(char) * strlen(value));
    strcpy(v_string, value);
    list_append(pool, vector->values, v_string);
}

void vector_add_UUID(Event_pool* pool, Vector* vector, uint8_t* value){
    uint8_t* v_uuid = pool->alloc(pool, sizeof(uint8_t) * 16);
    memcpy(v_uuid, value, 16);
    list_append(pool, vector->values, v_uuid);
}

Vector* vector_add_Vector(Event_pool* pool, Vector* vector, enum DataType datatype){
    Vector* v_vector = pool->alloc(pool, sizeof(Vector));
    v_vector->datatype = datatype;
    v_vector->values = list_create(pool);
    list_append(pool, vector->values, v_vector);
    return v_vector;
}

List* vector_add_Container(Event_pool* pool, Vector* vector){
    List* v_container = list_create(pool);
    list_append(pool, vector->values, v_container);
    return v_container;
}