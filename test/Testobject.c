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

void setUp (void) {}

void tearDown (void) {}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_seconds_in_timestamp);
    return UNITY_END();
}