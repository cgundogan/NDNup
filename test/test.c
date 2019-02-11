/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

static uint8_t buffer[128];

static ndnup_tlfield test_tlfield_encode_input_01a = 1;
static ndnup_tlfield test_tlfield_encode_input_01b = (1UL << 16) - 1;
static ndnup_tlfield test_tlfield_encode_input_01c = (1UL << 32) - 1;
static const uint8_t test_tlfield_encode_expected_01a[] = { 0x01 };
static const uint8_t test_tlfield_encode_expected_01b[] = { 253, 0xFF, 0xFF };
static const uint8_t test_tlfield_encode_expected_01c[] = { 254, 0xFF, 0xFF, 0xFF, 0xFF };

void test_tlfield_01(void)
{
    uint8_t offset = 0;

    offset = ndnup_encode_tlfield(buffer, test_tlfield_encode_input_01a);
    TEST_ASSERT_EQUAL_UINT(1, offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(test_tlfield_encode_expected_01a, buffer, offset);

    offset = ndnup_encode_tlfield(buffer, test_tlfield_encode_input_01b);
    TEST_ASSERT_EQUAL_UINT(3, offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(test_tlfield_encode_expected_01b, buffer, offset);

    offset = ndnup_encode_tlfield(buffer, test_tlfield_encode_input_01c);
    TEST_ASSERT_EQUAL_UINT(5, offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(test_tlfield_encode_expected_01c, buffer, offset);
}

int main(void)
{
    UNITY_BEGIN();
 
    RUN_TEST(test_tlfield_01);
 
    return UNITY_END();
}
