#include "unity.h"
#include "object.h"

void test_timestamp(void){
    uint64_t timestamp = generate_current_timestamp();
    TEST_ASSERT(timestamp > 0);
}

void setUp (void) {}

void tearDown (void) {}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_timestamp);
    return UNITY_END();
}