/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

extern void test_tlfield_encode_1byte(void);
extern void test_tlfield_encode_2byte(void);
extern void test_tlfield_encode_4byte(void);

extern void test_tlfield_decode_1byte(void);
extern void test_tlfield_decode_2byte(void);
extern void test_tlfield_decode_4byte(void);

extern void test_interest_encode(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tlfield_encode_1byte);
    RUN_TEST(test_tlfield_encode_2byte);
    RUN_TEST(test_tlfield_encode_4byte);

    RUN_TEST(test_tlfield_decode_1byte);
    RUN_TEST(test_tlfield_decode_2byte);
    RUN_TEST(test_tlfield_decode_4byte);

    RUN_TEST(test_interest_encode);

    return UNITY_END();
}
