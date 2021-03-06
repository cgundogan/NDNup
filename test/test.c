/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnv03/ndnup.h"

extern void test_tlv_encode_1byte(void);
extern void test_tlv_encode_2byte(void);
extern void test_tlv_encode_4byte(void);

extern void test_tlv_decode_1byte(void);
extern void test_tlv_decode_2byte(void);
extern void test_tlv_decode_4byte(void);

extern void test_interest_encode_simple(void);
extern void test_interest_encode_complex(void);

extern void test_interest_decode_simple(void);
extern void test_interest_decode_complex(void);

extern void test_data_encode_simple(void);
extern void test_data_encode_complex(void);

extern void test_data_decode_simple(void);
extern void test_data_decode_complex(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tlv_encode_1byte);
    RUN_TEST(test_tlv_encode_2byte);
    RUN_TEST(test_tlv_encode_4byte);

    RUN_TEST(test_tlv_decode_1byte);
    RUN_TEST(test_tlv_decode_2byte);
    RUN_TEST(test_tlv_decode_4byte);

    RUN_TEST(test_interest_encode_simple);
    RUN_TEST(test_interest_encode_complex);

    RUN_TEST(test_interest_decode_simple);
    RUN_TEST(test_interest_decode_complex);

    RUN_TEST(test_data_encode_simple);
    RUN_TEST(test_data_encode_complex);

    RUN_TEST(test_data_decode_simple);
    RUN_TEST(test_data_decode_complex);

    return UNITY_END();
}
