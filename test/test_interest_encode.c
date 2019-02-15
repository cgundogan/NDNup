/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"

static uint8_t buffer[128];

static ndnup_interest_t simple_interest = {
    .test = 0,
};
static uint8_t simple_interest_expected[] = {
    /* Outermost TLV with length 0 */
    0x05, 0x00,
};

void test_interest_encode(void) {
  int8_t error = 0;
  ndnup_buffer_write_t buf;

  ndnup_buffer_init(&buf, buffer, sizeof(buffer) / sizeof(buffer[0]));

  error = ndnup_interest_encode(&buf, &simple_interest);

  TEST_ASSERT_EQUAL_INT8(0, error);
  TEST_ASSERT_EQUAL_UINT(sizeof(simple_interest_expected) /
                             sizeof(simple_interest_expected[0]),
                         buf.offset);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(simple_interest_expected, buf.buffer,
                                buf.offset);
}
