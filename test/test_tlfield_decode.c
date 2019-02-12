/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

void test_tlfield_decode_01(void)
{
    uint8_t offset = 0;
    ndnup_tlfield_t tmp;

    uint8_t input_01[] = { 0xFC };
    ndnup_tlfield_t expected_01 = 252;

    offset = ndnup_decode_tlfield(input_01, &tmp);
    TEST_ASSERT_EQUAL_UINT(1, offset);
    TEST_ASSERT_EQUAL_INT64(expected_01, tmp);


    uint8_t input_02[] = { 253, 0xFF, 0xFF };
    ndnup_tlfield_t expected_02 = (1UL << 16) -1;

    offset = ndnup_decode_tlfield(input_02, &tmp);
    TEST_ASSERT_EQUAL_UINT(3, offset);
    TEST_ASSERT_EQUAL_INT64(expected_02, tmp);


    uint8_t input_03[] = { 254, 0xFF, 0xFF, 0xFF, 0xFF };
    ndnup_tlfield_t expected_03 = (1UL << 32) -1;

    offset = ndnup_decode_tlfield(input_03, &tmp);
    TEST_ASSERT_EQUAL_UINT(5, offset);
    TEST_ASSERT_EQUAL_INT64(expected_03, tmp);
}
