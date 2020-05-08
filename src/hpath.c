#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "event.h"
#include "object.h"

#define RAW_SIZE 1024 * 8

uint8_t* event_to_raw(Event* e) {
    uint8_t* raw = malloc(sizeof(uint8_t) * RAW_SIZE);
    uint64_t raw_size = 0;

    //Version. 1 byte
    memcpy(raw+raw_size, &(e->version), sizeof(uint8_t));
    raw_size+=sizeof(uint8_t);

    //Timestamp. 8 byte
    memcpy(raw+raw_size, &(e->timestamp), sizeof(uint64_t));
    raw_size+=sizeof(uint64_t);

    raw[raw_size] = '\n';

    return raw;
}

int main(){
    Event* e = malloc(sizeof(Event));
    e->version = 1;
    e->timestamp = 15276799200000000;
    printf("%d", event_to_raw(e));
    return 0;
}
