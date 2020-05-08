#include "unity.h"
#include "list.h"

void test_create_destroy_list(void){
    List* list = list_create();
    TEST_ASSERT_EQUAL_size_t(list->size, 0);
    TEST_ASSERT_NULL(list->el);
    list_free(list);
}

void test_one_element_list(void){
    uint64_t* element = malloc(sizeof(uint64_t));
    *element = 10;
    List* list = list_create();
    TEST_ASSERT_EQUAL_size_t(list->size, 0);
    TEST_ASSERT_NULL(list->el);
    list_append(list, element);
    TEST_ASSERT_EQUAL_size_t(list->size, 1);
    TEST_ASSERT_EQUAL_UINT64(*((uint64_t*)list_get_latest(list)->value), 10);
    list_delete_latest(list);
    TEST_ASSERT_EQUAL_size_t(list->size, 0);
    list_free(list);
}

void test_some_elements_list(void){
    uint64_t* el1 = malloc(sizeof(uint64_t));
    uint64_t* el2 = malloc(sizeof(uint64_t));
    uint64_t* el3 = malloc(sizeof(uint64_t));
    *el1 = 10;
    *el2 = 20;
    *el3 = 30;
    List* list = list_create();
    TEST_ASSERT_EQUAL_size_t(list->size, 0);
    TEST_ASSERT_NULL(list->el);
    list_append(list, el1);
    TEST_ASSERT_EQUAL_size_t(list->size, 1);
    TEST_ASSERT_EQUAL_UINT64(*((uint64_t*)list_get_latest(list)->value), 10);
    list_append(list, el2);
    TEST_ASSERT_EQUAL_size_t(list->size, 2);
    TEST_ASSERT_EQUAL_UINT64(*((uint64_t*)list_get_latest(list)->value), 20);
    list_delete_latest(list);
    TEST_ASSERT_EQUAL_size_t(list->size, 1);
    list_append(list, el3);
    TEST_ASSERT_EQUAL_size_t(list->size, 2);
    TEST_ASSERT_EQUAL_UINT64(*((uint64_t*)list_get_latest(list)->value), 30);
    list_free(list);
}

void setUp (void) {}

void tearDown (void) {}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_create_destroy_list);
    RUN_TEST(test_one_element_list);
    RUN_TEST(test_some_elements_list);
    return UNITY_END();
}