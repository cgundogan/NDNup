/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

void test_tlfield_encode_1byte(void)
{
    int8_t error = 0;
    ndnup_tlfield_t field = 0xFC;
    ndnup_buffer_write_t buf;
    uint8_t buffer[1];
    uint8_t expected[1] = { 0xFC };

    ndnup_buffer_init(&buf, buffer, sizeof(buffer)/sizeof(buffer[0]));

    error = ndnup_encode_tlfield(&buf, field);

    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(1, buf.offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf.buffer, buf.offset);
}

void test_tlfield_encode_2byte(void)
{
    int8_t error = 0;
    ndnup_tlfield_t field = (1UL << 16) -1;
    ndnup_buffer_write_t buf;
    uint8_t buffer[3];
    uint8_t expected[3] = { 253, 0xFF, 0xFF };

    ndnup_buffer_init(&buf, buffer, sizeof(buffer)/sizeof(buffer[0]));

    error = ndnup_encode_tlfield(&buf, field);

    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(3, buf.offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf.buffer, buf.offset);
}

void test_tlfield_encode_4byte(void)
{
    int8_t error = 0;
    ndnup_tlfield_t field = (1UL << 32) -1;
    ndnup_buffer_write_t buf;
    uint8_t buffer[5];
    uint8_t expected[5] = { 254, 0xFF, 0xFF, 0xFF, 0xFF };

    ndnup_buffer_init(&buf, buffer, sizeof(buffer)/sizeof(buffer[0]));

    error = ndnup_encode_tlfield(&buf, field);

    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(5, buf.offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf.buffer, buf.offset);
}
