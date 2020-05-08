#ifndef __OBJECT_INCLUDED
#define __OBJECT_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    Key key;
    enum DataType datatype;
    void* value;
} Tag;

typedef struct {
    enum DataType datatype;
    int32_t length;
    void* values;
} Vector;

typedef struct {
    uint16_t count;
    Tag* tags;
} Container;

typedef struct event {
    uint8_t version;
    uint64_t timestamp;
    uint8_t UUID[16];
    Container payload;
} Event;
#endif
