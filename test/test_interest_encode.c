/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"
#include "interest.h"

static uint8_t buffer[128];

static ndn_interest_t simple_interest = {
    .name =
        {
            .components = {{.type = tlv_generic_name_component,
                            .size = 3,
                            .value = {'h', 'a', 'w'}},
                           {.type = tlv_generic_name_component,
                            .size = 3,
                            .value = {'m', 's', 'a'}}},
            .components_size = 2,
        },
    .nonce = 0x000000FF,
    .can_be_prefix_enabled = 0,
    .must_be_fresh_enabled = 0,
    .parameters_enabled = 0,
    .hop_limit_enabled = 0,
};
static uint8_t simple_interest_expected[] = {
    /* Outermost TLV with length 18 */
    0x05, 0x12,
    /* Name */
    0x07, 0x0A,
    /* GenericNameComponent "haw" */
    0x08, 0x03, 0x68, 0x61, 0x77,
    /* GenericNameComponent "msa" */
    0x08, 0x03, 0x6d, 0x73, 0x61,
    /* Nonce */
    0x0A, 0x04, 0x00, 0x00, 0x00, 0xFF,
};

static ndn_interest_t interest_cbp_mbf_il_hl = {
    .name =
        {
            .components = {{.type = tlv_generic_name_component,
                            .size = 3,
                            .value = {'h', 'a', 'w'}},
                           {.type = tlv_generic_name_component,
                            .size = 3,
                            .value = {'m', 's', 'a'}}},
            .components_size = 2,
        },
    .nonce = 0x000000FF,
    .can_be_prefix_enabled = 1,
    .must_be_fresh_enabled = 1,
    .parameters_enabled = 0,
    .hop_limit_enabled = 1,
    .hop_limit = 64,
    .lifetime_enabled = 1,
    .lifetime = 0x0001FFFF,
};
static uint8_t interest_cbp_mbf_il_hl_expected[] = {
    /* Outermost TLV with length 32 */
    0x05, 0x1F,
    /* Name */
    0x07, 0x0A,
    /* GenericNameComponent "haw" */
    0x08, 0x03, 0x68, 0x61, 0x77,
    /* GenericNameComponent "msa" */
    0x08, 0x03, 0x6d, 0x73, 0x61,
    /* CanBePrefix */
    0x21, 0x00,
    /* MustBeFresh */
    0x12, 0x00,
    /* Nonce */
    0x0A, 0x04, 0x00, 0x00, 0x00, 0xFF,
    /* Lifetime */
    0x0C, 0x04, 0x00, 0x01, 0xFF, 0xFF,
    /* HopLimit */
    0x22, 0x01, 0x40,
};

void test_interest_encode_simple(void) {
  int8_t error = 0;
  ndnup_buffer_write_t buf;

  ndnup_buffer_init(&buf, buffer, sizeof(buffer) / sizeof(buffer[0]));

  error = interest_encode(&buf, &simple_interest);

  TEST_ASSERT_EQUAL_INT8(0, error);
  TEST_ASSERT_EQUAL_UINT(sizeof(simple_interest_expected) /
                             sizeof(simple_interest_expected[0]),
                         buf.offset);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(simple_interest_expected, buf.buffer,
                                buf.offset);
}

void test_interest_encode_cbp_mbf_il_hl(void) {
  int8_t error = 0;
  ndnup_buffer_write_t buf;

  ndnup_buffer_init(&buf, buffer, sizeof(buffer) / sizeof(buffer[0]));

  error = interest_encode(&buf, &interest_cbp_mbf_il_hl);

  TEST_ASSERT_EQUAL_INT8(0, error);
  TEST_ASSERT_EQUAL_UINT(sizeof(interest_cbp_mbf_il_hl_expected) /
                             sizeof(interest_cbp_mbf_il_hl_expected[0]),
                         buf.offset);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(interest_cbp_mbf_il_hl_expected, buf.buffer,
                                buf.offset);
}
