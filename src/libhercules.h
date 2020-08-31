#ifndef __OBJECT_INCLUDED
#define __OBJECT_INCLUDED

#include "list.h"
#include "pool.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include <inttypes.h>

#define tag_get_Byte(tag) (*((uint8_t*) tag->value))
#define tag_get_Short(tag) (*((int16_t*) tag->value))
#define tag_get_Integer(tag) (*((int32_t*) tag->value))
#define tag_get_Long(tag) (*((int64_t*) tag->value))
#define tag_get_Flag(tag) (*((char*) tag->value) == 0 ? 0 : 1)
#define tag_get_Float(tag) (*((float*) tag->value))
#define tag_get_Double(tag) (*((double*) tag->value))
#define tag_get_String(tag) ((char*) tag->value)
#define tag_get_UUID(tag) ((uint8_t*) tag->value)
#define tag_get_Vector(tag) ((Vector*) tag->value)
#define tag_get_Container(tag) ((List*) tag->value)

#define try_realloc_binary_string(size, binary_string, binary_size, binary_max_size) \
  if(*binary_max_size - *binary_size < (size_t) size){\
    *binary_max_size *= 2; \
    binary_string = realloc(binary_string, *binary_max_size); \
  }

#define pack_be_uint8(value, binary_string, binary_size, binary_max_size) \
  try_realloc_binary_string(1, binary_string, binary_size, binary_max_size);\
  binary_string[(*binary_size)++] = value

#define pack_be_uint16(value, binary_string, binary_size, binary_max_size) \
  try_realloc_binary_string(2, binary_string, binary_size, binary_max_size);\
  binary_string[(*binary_size)++] = (uint8_t) (value  & 0x00FF);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0xFF00) >> 8);

#define pack_be_uint32(value, binary_string, binary_size, binary_max_size) \
  try_realloc_binary_string(4, binary_string, binary_size, binary_max_size);\
  binary_string[(*binary_size)++] = (uint8_t) (value  & 0x000000FF);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x0000FF00) >> 8);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x00FF0000) >> 16);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0xFF000000) >> 24);

#define pack_be_uint64(value, binary_string, binary_size, binary_max_size) \
  try_realloc_binary_string(8, binary_string, binary_size, binary_max_size);\
  binary_string[(*binary_size)++] = (uint8_t) (value  & 0x00000000000000FF);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x000000000000FF00) >> 8);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x0000000000FF0000) >> 16);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x00000000FF000000) >> 24);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x000000FF00000000) >> 32);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x0000FF0000000000) >> 40);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0x00FF000000000000) >> 48);\
  binary_string[(*binary_size)++] = (uint8_t) ((value & 0xFF00000000000000) >> 56)

#define pack_be_uint8_array(value, size, binary_string, binary_size, binary_max_size) \
  try_realloc_binary_string(size, binary_string, binary_size, binary_max_size);\
  for(size_t i = 0; i < (size_t) size; ++i){\
    binary_string[(*binary_size)++] = value[i];\
  }

enum DataType {
    CONTAINER = 0x01,
    BYTE = 0x02,
    SHORT = 0x03,
    INTEGER = 0x04,
    LONG = 0x05,
    FLAG = 0x06,
    FLOAT = 0x07,
    DOUBLE = 0x08,
    STRING = 0x09,
    UUID = 0x0A,
    NULL_TYPE = 0x0B,
    VECTOR = 0x80,
    RESERVED = 0xFF
};

typedef struct {
    int8_t length;
    char value[];
} Key;

typedef struct {
    enum DataType datatype;
    void* value;
    Key key;
} Tag;

typedef struct {
    enum DataType datatype;
    List* values;
} Vector;

typedef struct event {
    Event_pool* pool;
    uint8_t version;
    uint64_t timestamp;
    uint8_t UUID[16];
    List* payload;
} Event;

typedef struct event_binary {
    size_t size;
    char value[];
} Event_binary;

uint64_t generate_current_timestamp();
void generate_uuid_v4(uint8_t* uuid);
Event* event_create(Event_pool* pool, uint8_t version, uint64_t timestamp, uint8_t* uuid);
void event_free(Event* event);
void container_free(Event_pool* pool, List* container);
void vector_free(Event_pool* pool, Vector* vector);
Event* create_event(Event_pool* pool);
Tag* container_find_tag(List* list, int8_t key_length, char* key_name);
Tag* container_add_tag_Byte(Event_pool* pool, List* list, int8_t key_length, char* key_name, uint8_t value);
Tag* container_add_tag_Short(Event_pool* pool, List* list, int8_t key_length, char* key_name, int16_t value);
Tag* container_add_tag_Integer(Event_pool* pool, List* list, int8_t key_length, char* key_name, int32_t value);
Tag* container_add_tag_Long(Event_pool* pool, List* list, int8_t key_length, char* key_name, int64_t value);
Tag* container_add_tag_Flag(Event_pool* pool, List* list, int8_t key_length, char* key_name, char value);
Tag* container_add_tag_Float(Event_pool* pool, List* list, int8_t key_length, char* key_name, float value);
Tag* container_add_tag_Double(Event_pool* pool, List* list, int8_t key_length, char* key_name, double value);
Tag* container_add_tag_String(Event_pool* pool, List* list, int8_t key_length, char* key_name, char* value);
Tag* container_add_tag_UUID(Event_pool* pool, List* list, int8_t key_length, char* key_name, uint8_t* value);
Tag* container_add_tag_Null(Event_pool* pool, List* list, int8_t key_length, char* key_name);
Tag* container_add_tag_Vector(Event_pool* pool, List* list, enum DataType datatype, int8_t key_length, char* key_name);
Tag* container_add_tag_Container(Event_pool* pool, List* list, int8_t key_length, char* key_name);
char* event_to_bin(Event* event, size_t* binary_size);
char* container_to_bin(Event_pool* pool, List* container, char* binary_string, size_t* binary_size, size_t* binary_max_size);
char* vector_to_bin(Event_pool* pool, Vector* vector, char* binary_string, size_t* binary_size, size_t* binary_max_size);
void vector_add_Byte(Event_pool* pool, Vector* vector, uint8_t value);
void vector_add_Short(Event_pool* pool, Vector* vector, int16_t value);
void vector_add_Integer(Event_pool* pool, Vector* vector, int32_t value);
void vector_add_Long(Event_pool* pool, Vector* vector, int64_t value);
void vector_add_Flag(Event_pool* pool, Vector* vector, char value);
void vector_add_Float(Event_pool* pool, Vector* vector, float value);
void vector_add_Double(Event_pool* pool, Vector* vector, double value);
void vector_add_String(Event_pool* pool, Vector* vector, char* value);
void vector_add_UUID(Event_pool* pool, Vector* vector, uint8_t* value);
Vector* vector_add_Vector(Event_pool* pool, Vector* vector, enum DataType datatype);
List* vector_add_Container(Event_pool* pool, Vector* vector);
#endif
