/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"
#include "interest.h"

static uint8_t buffer[128];

static ndn_interest_t simple_interest = {
    .nonce = 0xFF,
    .can_be_prefix_enabled = 0,
    .must_be_fresh_enabled = 0,
    .parameters_enabled = 0,
    .hop_limit_enabled = 0,
};
static uint8_t simple_interest_expected[] = {
    /* Outermost TLV with length 0 */
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

void test_interest_encode(void) {
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
