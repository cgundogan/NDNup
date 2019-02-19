/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

void test_tlv_decode_1byte(void)
{
    int8_t error = 0;
    tlfield_t tmp;
    ndnup_buffer_read_t buf;

    uint8_t input[] = {0xFC};
    tlfield_t expected = 0xFC;

    ndnup_buffer_init(&buf, input, sizeof(input)/sizeof(input[0]));

    error = tlfield_decode(&buf, &tmp);
    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(1, buf.offset);
    TEST_ASSERT_EQUAL_INT64(expected, tmp);
}

void test_tlv_decode_2byte(void)
{
    int8_t error = 0;
    tlfield_t tmp;
    ndnup_buffer_t buf;

    uint8_t input[] = { 253, 0xFF, 0xFF };
    tlfield_t expected = (1UL << 16) -1;

    ndnup_buffer_init(&buf, input, sizeof(input)/sizeof(input[0]));

    error = tlfield_decode(&buf, &tmp);
    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(3, buf.offset);
    TEST_ASSERT_EQUAL_INT64(expected, tmp);
}

void test_tlv_decode_4byte(void)
{
    int8_t error = 0;
    tlfield_t tmp;
    ndnup_buffer_t buf;

    uint8_t input[] = { 254, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    tlfield_t expected = (1UL << 32) -1;

    ndnup_buffer_init(&buf, input, sizeof(input)/sizeof(input[0]));

    error = tlfield_decode(&buf, &tmp);
    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(5, buf.offset);
    TEST_ASSERT_EQUAL_INT64(expected, tmp);
}
