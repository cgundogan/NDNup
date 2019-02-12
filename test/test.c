/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

extern void test_tlfield_encode_01(void);
extern void test_tlfield_decode_01(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tlfield_encode_01);
    RUN_TEST(test_tlfield_decode_01);

    return UNITY_END();
}
