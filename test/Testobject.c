#include "unity.h"
#include "object.h"
#include <time.h>

void test_seconds_in_timestamp(void){
    uint64_t timestamp = generate_current_timestamp();
    struct timespec* t = malloc(sizeof(struct timespec));
    clock_gettime(CLOCK_REALTIME, t);
    TEST_ASSERT_EQUAL_INT64(t->tv_sec, timestamp / 10000000);
    free(t);
}

void test_nanoseconds_in_timestamp(void){
    uint64_t timestamp = generate_current_timestamp();
    struct timespec* t = malloc(sizeof(struct timespec));
    clock_gettime(CLOCK_REALTIME, t);
    TEST_ASSERT_GREATER_OR_EQUAL_INT64(timestamp % 10000000, t->tv_nsec / 100);
    free(t);
}

void test_event_create(void){
    uint8_t* uuid = malloc(sizeof(uint8_t) * 16);
    generate_uuid_v4(uuid);
    uint64_t timestamp = generate_current_timestamp();
    Event* event = event_create(0x01, timestamp, uuid);
    TEST_ASSERT_EQUAL_UINT64(timestamp, event->timestamp);
    TEST_ASSERT_EQUAL_UINT8(0x01, event->version);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(uuid, event->UUID, 16);
    event_free(event);
}

void setUp (void) {}

void tearDown (void) {}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_seconds_in_timestamp);
    RUN_TEST(test_nanoseconds_in_timestamp);
    RUN_TEST(test_event_create);
    return UNITY_END();
}