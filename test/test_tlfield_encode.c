/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

void test_tlfield_encode_01(void)
{
    uint8_t test_buffer[16];
    uint8_t offset = 0;

    ndnup_tlfield_t input_01 = 252;
    uint8_t expected_01[] = { 0xFC };

    offset = ndnup_encode_tlfield(test_buffer, input_01);
    TEST_ASSERT_EQUAL_UINT(1, offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_01, test_buffer, offset);

    ndnup_tlfield_t input_02 = (1UL << 16) - 1;
    uint8_t expected_02[] = { 253, 0xFF, 0xFF };

    offset = ndnup_encode_tlfield(test_buffer, input_02);
    TEST_ASSERT_EQUAL_UINT(3, offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_02, test_buffer, offset);

    ndnup_tlfield_t input_03 = (1UL << 32) - 1;
    uint8_t expected_03[] = { 254, 0xFF, 0xFF, 0xFF, 0xFF };

    offset = ndnup_encode_tlfield(test_buffer, input_03);
    TEST_ASSERT_EQUAL_UINT(5, offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_03, test_buffer, offset);
}
