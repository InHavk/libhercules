#include "unity.h"
#include "libhercules.h"
#include <time.h>
#include <inttypes.h>

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

void test_event_with_container(void){
    uint8_t* uuid = malloc(sizeof(uint8_t) * 16);
    generate_uuid_v4(uuid);
    uint64_t timestamp = generate_current_timestamp();
    Event* event = event_create(0x01, timestamp, uuid);
    
    // add Tag "byte" with type Byte and value 55
    Tag* tag1_i = container_add_tag_Byte(event->payload, 4, "byte", 55);
    // direct check
    TEST_ASSERT_EQUAL_UINT8(55, *((uint8_t*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(4, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("byte", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag1 = container_find_tag(event->payload, 4, "byte");
    TEST_ASSERT_NOT_NULL(tag1);
    TEST_ASSERT_NOT_NULL(tag1->value);
    TEST_ASSERT_EQUAL_UINT8(55, tag_get_Byte(tag1));
    TEST_ASSERT_EQUAL_INT8(4, tag1->key.length);
    TEST_ASSERT_EQUAL_STRING("byte", tag1->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag1_i);
    TEST_ASSERT_NOT_NULL(tag1_i->value);
    TEST_ASSERT_EQUAL_UINT8(55, tag_get_Byte(tag1_i));
    TEST_ASSERT_EQUAL_INT8(4, tag1_i->key.length);
    TEST_ASSERT_EQUAL_STRING("byte", tag1_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(BYTE, tag1->datatype);

    // add Tag "short" with type Short and value 1024
    Tag* tag2_i = container_add_tag_Short(event->payload, 5, "short", 1024);
    // direct check
    TEST_ASSERT_EQUAL_INT16(1024, *((int16_t*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(5, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("short", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal test
    Tag* tag2 = container_find_tag(event->payload, 5, "short");
    TEST_ASSERT_NOT_NULL(tag2);
    TEST_ASSERT_NOT_NULL(tag2->value);
    TEST_ASSERT_EQUAL_INT16(1024, tag_get_Short(tag2));
    TEST_ASSERT_EQUAL_INT8(5, tag2->key.length);
    TEST_ASSERT_EQUAL_STRING("short", tag2->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag2_i);
    TEST_ASSERT_NOT_NULL(tag2_i->value);
    TEST_ASSERT_EQUAL_INT16(1024, tag_get_Short(tag2_i));
    TEST_ASSERT_EQUAL_INT8(5, tag2_i->key.length);
    TEST_ASSERT_EQUAL_STRING("short", tag2_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(SHORT, tag2->datatype);

    // add Tag "integer" with type Integer and value 1048576
    Tag* tag3_i = container_add_tag_Integer(event->payload, 7, "integer", 1048576);
    // direct check
    TEST_ASSERT_EQUAL_INT32(1048576, *((int32_t*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(7, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("integer", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal test
    Tag* tag3 = container_find_tag(event->payload, 7, "integer");
    TEST_ASSERT_NOT_NULL(tag3);
    TEST_ASSERT_NOT_NULL(tag3->value);
    TEST_ASSERT_EQUAL_INT32(1048576, tag_get_Integer(tag3));
    TEST_ASSERT_EQUAL_INT8(7, tag3->key.length);
    TEST_ASSERT_EQUAL_STRING("integer", tag3->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag3_i);
    TEST_ASSERT_NOT_NULL(tag3_i->value);
    TEST_ASSERT_EQUAL_INT32(1048576, tag_get_Integer(tag3_i));
    TEST_ASSERT_EQUAL_INT8(7, tag3_i->key.length);
    TEST_ASSERT_EQUAL_STRING("integer", tag3_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(INTEGER, tag3->datatype);

    // add Tag "long" with type Long and value 274877906944
    Tag* tag4_i = container_add_tag_Long(event->payload, 4, "long", 274877906944);
    // direct check
    TEST_ASSERT_EQUAL_INT64(274877906944, *((int64_t*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(4, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("long", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag4 = container_find_tag(event->payload, 4, "long");
    TEST_ASSERT_NOT_NULL(tag4);
    TEST_ASSERT_NOT_NULL(tag4->value);
    TEST_ASSERT_EQUAL_INT64(274877906944, tag_get_Long(tag4));
    TEST_ASSERT_EQUAL_INT8(4, tag4->key.length);
    TEST_ASSERT_EQUAL_STRING("long", tag4->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag4_i);
    TEST_ASSERT_NOT_NULL(tag4_i->value);
    TEST_ASSERT_EQUAL_INT64(274877906944, tag_get_Long(tag4_i));
    TEST_ASSERT_EQUAL_INT8(4, tag4_i->key.length);
    TEST_ASSERT_EQUAL_STRING("long", tag4_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(LONG, tag4->datatype);

    // add Tag "flag" with type Flag and value 1
    Tag* tag5_i = container_add_tag_Flag(event->payload, 4, "flag", 1);
    // direct check
    TEST_ASSERT_EQUAL(1, *((char*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(4, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("flag", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag5 = container_find_tag(event->payload, 4, "flag");
    TEST_ASSERT_NOT_NULL(tag5);
    TEST_ASSERT_NOT_NULL(tag5->value);
    TEST_ASSERT_EQUAL(1, tag_get_Flag(tag5));
    TEST_ASSERT_EQUAL_INT8(4, tag5->key.length);
    TEST_ASSERT_EQUAL_STRING("flag", tag5->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag5_i);
    TEST_ASSERT_NOT_NULL(tag5_i->value);
    TEST_ASSERT_EQUAL(1, tag_get_Flag(tag5_i));
    TEST_ASSERT_EQUAL_INT8(4, tag5_i->key.length);
    TEST_ASSERT_EQUAL_STRING("flag", tag5_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(FLAG, tag5->datatype);

    // add Tag "float" with type Float and value 32.0f
    Tag* tag6_i = container_add_tag_Float(event->payload, 5, "float", 32.0f);
    // direct check
    TEST_ASSERT_EQUAL_FLOAT(32.0f, *((float*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(5, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("float", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag6 = container_find_tag(event->payload, 5, "float");
    TEST_ASSERT_NOT_NULL(tag6);
    TEST_ASSERT_NOT_NULL(tag6->value);
    TEST_ASSERT_EQUAL_FLOAT(32.0f, tag_get_Float(tag6));
    TEST_ASSERT_EQUAL_INT8(5, tag6->key.length);
    TEST_ASSERT_EQUAL_STRING("float", tag6->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag6_i);
    TEST_ASSERT_NOT_NULL(tag6_i->value);
    TEST_ASSERT_EQUAL_FLOAT(32.0f, tag_get_Float(tag6_i));
    TEST_ASSERT_EQUAL_INT8(5, tag6_i->key.length);
    TEST_ASSERT_EQUAL_STRING("float", tag6_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(FLOAT, tag6->datatype);

    // add Tag "double" with type Double and value 64.0
    Tag* tag7_i = container_add_tag_Double(event->payload, 6, "double", 64.0);
    // direct check
    TEST_ASSERT_EQUAL(64.0, *((double*) ((Tag*) (list_get_latest(event->payload)->value))->value));
    TEST_ASSERT_EQUAL_INT8(6, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("double", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag7 = container_find_tag(event->payload, 6, "double");
    TEST_ASSERT_NOT_NULL(tag7);
    TEST_ASSERT_NOT_NULL(tag7->value);
    TEST_ASSERT_EQUAL(64.0, tag_get_Double(tag7));
    TEST_ASSERT_EQUAL_INT8(6, tag7->key.length);
    TEST_ASSERT_EQUAL_STRING("double", tag7->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag7_i);
    TEST_ASSERT_NOT_NULL(tag7_i->value);
    TEST_ASSERT_EQUAL(64.0, tag_get_Double(tag7_i));
    TEST_ASSERT_EQUAL_INT8(6, tag7_i->key.length);
    TEST_ASSERT_EQUAL_STRING("double", tag7_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(DOUBLE, tag7->datatype);

    // add Tag "string" with type String and value "test string"
    Tag* tag8_i = container_add_tag_String(event->payload, 6, "string", "test string");
    // direct check
    TEST_ASSERT_EQUAL_STRING("test string", (char*) ((Tag*) (list_get_latest(event->payload)->value))->value);
    TEST_ASSERT_EQUAL_INT8(6, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("string", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag8 = container_find_tag(event->payload, 6, "string");
    TEST_ASSERT_NOT_NULL(tag8);
    TEST_ASSERT_NOT_NULL(tag8->value);
    TEST_ASSERT_EQUAL_STRING("test string", tag_get_String(tag8));
    TEST_ASSERT_EQUAL_INT8(6, tag8->key.length);
    TEST_ASSERT_EQUAL_STRING("string", tag8->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag8_i);
    TEST_ASSERT_NOT_NULL(tag8_i->value);
    TEST_ASSERT_EQUAL_STRING("test string", tag_get_String(tag8_i));
    TEST_ASSERT_EQUAL_INT8(6, tag8_i->key.length);
    TEST_ASSERT_EQUAL_STRING("string", tag8_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(STRING, tag8->datatype);

    // add Tag "uuid" with type UUID and value 0x5f, 0x3e, 0x88, 0xbb, 0x23, 0xf0, 0xfe, 0x97, 0xcb, 0xc5, 0xe2, 0x3d, 0x82, 0xdd, 0x3e, 0xca
    uint8_t uuid_value[16] = {0x5f, 0x3e, 0x88, 0xbb, 0x23, 0xf0, 0xfe, 0x97, 0xcb, 0xc5, 0xe2, 0x3d, 0x82, 0xdd, 0x3e, 0xca};
    Tag* tag9_i = container_add_tag_UUID(event->payload, 4, "uuid", uuid_value);
    // direct check
    TEST_ASSERT_EQUAL_UINT8_ARRAY(uuid_value, (uint8_t*) ((Tag*) (list_get_latest(event->payload)->value))->value, 16);
    TEST_ASSERT_EQUAL_INT8(4, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("uuid", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag9 = container_find_tag(event->payload, 4, "uuid");
    TEST_ASSERT_NOT_NULL(tag9);
    TEST_ASSERT_NOT_NULL(tag9->value);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(uuid_value, tag_get_UUID(tag9), 16);
    TEST_ASSERT_EQUAL_INT8(4, tag9->key.length);
    TEST_ASSERT_EQUAL_STRING("uuid", tag9->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag9_i);
    TEST_ASSERT_NOT_NULL(tag9_i->value);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(uuid_value, tag_get_UUID(tag9_i), 16);
    TEST_ASSERT_EQUAL_INT8(4, tag9_i->key.length);
    TEST_ASSERT_EQUAL_STRING("uuid", tag9_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(UUID, tag9->datatype);

    // add Tag "null" with type Null
    Tag* tag10_i = container_add_tag_Null(event->payload, 4, "null");
    // direct check
    TEST_ASSERT_EQUAL_INT8(4, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("null", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag10 = container_find_tag(event->payload, 4, "null");
    TEST_ASSERT_NOT_NULL(tag10);
    TEST_ASSERT_EQUAL_INT8(4, tag10->key.length);
    TEST_ASSERT_EQUAL_STRING("null", tag10->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag10_i);
    TEST_ASSERT_EQUAL_INT8(4, tag10_i->key.length);
    TEST_ASSERT_EQUAL_STRING("null", tag10_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(NULL_TYPE, tag10->datatype);


    // add Tag "vector" with type Vector
    Tag* tag11_i = container_add_tag_Vector(event->payload, NULL_TYPE, 6, "vector");
    // direct check
    TEST_ASSERT_EQUAL_size_t(0, (size_t) ((List*)((Vector*)((Tag*) (list_get_latest(event->payload)->value))->value)->values)->size);
    TEST_ASSERT_NULL((List_element*)((List*)((Vector*)((Tag*) (list_get_latest(event->payload)->value))->value)->values)->el);
    TEST_ASSERT_EQUAL(NULL_TYPE, (List*)((Vector*)((Tag*) (list_get_latest(event->payload)->value))->value)->datatype);
    TEST_ASSERT_EQUAL_INT8(6, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("vector", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag11 = container_find_tag(event->payload, 6, "vector");
    TEST_ASSERT_NOT_NULL(tag11);
    TEST_ASSERT_NOT_NULL(tag11->value);
    TEST_ASSERT_EQUAL_size_t(0, tag_get_Vector(tag11)->values->size);
    TEST_ASSERT_NULL(tag_get_Vector(tag11)->values->el);
    TEST_ASSERT_EQUAL(NULL_TYPE, tag_get_Vector(tag11)->datatype);
    TEST_ASSERT_EQUAL_INT8(6, tag11->key.length);
    TEST_ASSERT_EQUAL_STRING("vector", tag11->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag11_i);
    TEST_ASSERT_NOT_NULL(tag11_i->value);
    TEST_ASSERT_EQUAL_size_t(0, tag_get_Vector(tag11_i)->values->size);
    TEST_ASSERT_NULL(tag_get_Vector(tag11_i)->values->el);
    TEST_ASSERT_EQUAL(NULL_TYPE, tag_get_Vector(tag11_i)->datatype);
    TEST_ASSERT_EQUAL_INT8(6, tag11_i->key.length);
    TEST_ASSERT_EQUAL_STRING("vector", tag11_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(VECTOR, tag11->datatype);

    // add Tag "container" with type Container
    Tag* tag12_i = container_add_tag_Container(event->payload, 9, "container");
    // direct check
    TEST_ASSERT_EQUAL_size_t(0, (size_t) ((List*) ((Tag*) (list_get_latest(event->payload)->value))->value)->size);
    TEST_ASSERT_NULL((List_element*) ((List*) ((Tag*) (list_get_latest(event->payload)->value))->value)->el);
    TEST_ASSERT_EQUAL_INT8(9, ((Tag*) (list_get_latest(event->payload)->value))->key.length);
    TEST_ASSERT_EQUAL_STRING("container", ((Tag*) (list_get_latest(event->payload)->value))->key.value);
    // normal check
    Tag* tag12 = container_find_tag(event->payload, 9, "container");
    TEST_ASSERT_NOT_NULL(tag12);
    TEST_ASSERT_NOT_NULL(tag12->value);
    TEST_ASSERT_EQUAL_size_t(0, tag_get_Container(tag12)->size);
    TEST_ASSERT_NULL(tag_get_Container(tag12)->el);
    TEST_ASSERT_EQUAL_INT8(9, tag12->key.length);
    TEST_ASSERT_EQUAL_STRING("container", tag12->key.value);
    // return check
    TEST_ASSERT_NOT_NULL(tag12_i);
    TEST_ASSERT_NOT_NULL(tag12_i->value);
    TEST_ASSERT_EQUAL_size_t(0, tag_get_Container(tag12_i)->size);
    TEST_ASSERT_NULL(tag_get_Container(tag12_i)->el);
    TEST_ASSERT_EQUAL_INT8(9, tag12_i->key.length);
    TEST_ASSERT_EQUAL_STRING("container", tag12_i->key.value);
    // type check
    TEST_ASSERT_EQUAL(CONTAINER, tag12->datatype);

    event_free(event);
}

void test_event_to_binary(void){
    uint8_t* uuid = malloc(sizeof(uint8_t) * 16);
    generate_uuid_v4(uuid);
    uuid[0] = 0x5e;
    uuid[1] = 0xf1;
    uuid[2] = 0x82;
    uuid[3] = 0x39;
    uuid[4] = 0x8e;
    uuid[5] = 0x6c;
    uuid[6] = 0x4e;
    uuid[7] = 0x19;
    uuid[8] = 0xb2;
    uuid[9] = 0x22;
    uuid[10] = 0xc8;
    uuid[11] = 0x7f;
    uuid[12] = 0xd0;
    uuid[13] = 0x6b;
    uuid[14] = 0x00;
    uuid[15] = 0x3d;
    uint64_t timestamp = 15276799200000000;
    Event* event = event_create(0x01, timestamp, uuid);
    
    container_add_tag_String(event->payload, 10, "String tag", "String value");
    container_add_tag_Null(event->payload, 8, "Null tag");
    container_add_tag_UUID(event->payload, 8, "Uuid tag", uuid);
    container_add_tag_Vector(event->payload, CONTAINER, 19, "Container array tag");
    Tag* tag = container_find_tag(event->payload, 19, "Container array tag");
    vector_add_Container((Vector*) tag->value);
    container_add_tag_Integer(list_get_latest(((Vector*) tag->value)->values)->value, 16, "Some integer tag", 123345567);
    vector_add_Container((Vector*) tag->value);
    container_add_tag_Vector(list_get_latest(((Vector*) tag->value)->values)->value, BYTE, 15, "Byte vector tag");
    tag = container_find_tag(list_get_latest(((Vector*) tag->value)->values)->value, 15, "Byte vector tag");
    vector_add_Byte((Vector*) tag->value, -34);
    vector_add_Byte((Vector*) tag->value, -83);
    vector_add_Byte((Vector*) tag->value, -66);
    vector_add_Byte((Vector*) tag->value, -17);

    size_t* event_binary_size = malloc(sizeof(size_t));
    char* event_binary = event_to_bin(event, event_binary_size);

    char origin_message[169] = {0x01, 0x00, 0x36, 0x46, 0x2a, 0xfd, 0x9e, 0xf8, 0x00, 0x5e, 0xf1, 0x82, 0x39, 0x8e, 0x6c,\
                            0x4e, 0x19, 0xb2, 0x22, 0xc8, 0x7f, 0xd0, 0x6b, 0x00, 0x3d, 0x00, 0x04, 0x0a, 0x53, 0x74,\
                            0x72, 0x69, 0x6e, 0x67, 0x20, 0x74, 0x61, 0x67, 0x09, 0x00, 0x00, 0x00, 0x0c, 0x53, 0x74,\
                            0x72, 0x69, 0x6e, 0x67, 0x20, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x08, 0x4e, 0x75, 0x6c, 0x6c,\
                            0x20, 0x74, 0x61, 0x67, 0x0b, 0x08, 0x55, 0x75, 0x69, 0x64, 0x20, 0x74, 0x61, 0x67, 0x0a,\
                            0x5e, 0xf1, 0x82, 0x39, 0x8e, 0x6c, 0x4e, 0x19, 0xb2, 0x22, 0xc8, 0x7f, 0xd0, 0x6b, 0x00,\
                            0x3d, 0x13, 0x43, 0x6f, 0x6e, 0x74, 0x61, 0x69, 0x6e, 0x65, 0x72, 0x20, 0x61, 0x72, 0x72,\
                            0x61, 0x79, 0x20, 0x74, 0x61, 0x67, 0x80, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x10,\
                            0x53, 0x6f, 0x6d, 0x65, 0x20, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x20, 0x74, 0x61,\
                            0x67, 0x04, 0x07, 0x5a, 0x1a, 0x9f, 0x00, 0x01, 0x0f, 0x42, 0x79, 0x74, 0x65, 0x20, 0x76,\
                            0x65, 0x63, 0x74, 0x6f, 0x72, 0x20, 0x74, 0x61, 0x67, 0x80, 0x02, 0x00, 0x00, 0x00, 0x04,\
                            0xde, 0xad, 0xbe, 0xef};
    TEST_ASSERT_EQUAL_CHAR_ARRAY(origin_message, event_binary, 169);

    free(event_binary_size);
    free(event_binary);
    event_free(event);
}

void setUp (void) {}

void tearDown (void) {}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_seconds_in_timestamp);
    RUN_TEST(test_nanoseconds_in_timestamp);
    RUN_TEST(test_event_create);
    RUN_TEST(test_event_with_container);
    RUN_TEST(test_event_to_binary);
    return UNITY_END();
}