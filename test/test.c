/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

static const uint8_t buffer[128];

static const ndnup_tlfield test_tlfield_encode_input_01 = 1;
static const uint8_t test_tlfield_encode_expected_01[] = { 0x01 };

void test_tlfield_01(void)
{
    uint8_t offset = 0;

    offset = ndnup_encode_tlfield(buffer, test_tlfield_encode_input_01);

    TEST_ASSERT_EQUAL_UINT(1, offset);
}

int main(void)
{
    UNITY_BEGIN();
 
    RUN_TEST(test_tlfield_01);
 
    return UNITY_END();
}
