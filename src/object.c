#include "object.h"
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
    list_free(event->payload);
    free(event);
}

Event* create_event() {
    uint8_t* uuid = malloc(sizeof(uint8_t) * 16);
    generate_uuid_v4(uuid);
    Event* event = event_create(0x01, generate_current_timestamp(), uuid);
    free(uuid);
    return event;
}