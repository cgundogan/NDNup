/*
 * Copyright (C) 2019 HAW Hamburg
 *
 */

#include "unity.h"
#include "ndnup.h"
#include "data.h"

static uint8_t buffer[128];

static ndn_data_t simple_data = {
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
    .metainfo_enabled = 0,
    .contenttype_enabled = 0,
    .freshnessperiod_enabled = 0,
    .finalblockid_enabled = 0,
    .content_enabled = 0,
};
static uint8_t simple_data_buffer[] = {
    /* Outermost TLV */
    0x06, 0x0C,
    /* Name */
    0x07, 0x0A,
    /* GenericNameComponent "haw" */
    0x08, 0x03, 0x68, 0x61, 0x77,
    /* GenericNameComponent "msa" */
    0x08, 0x03, 0x6d, 0x73, 0x61,
};

void test_data_encode_simple(void) {
    int8_t error = 0;
    buffer_write_t buf;

    buffer_init(&buf, buffer, sizeof(buffer) / sizeof(buffer[0]));

    error = data_encode(&buf, &simple_data);

    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(sizeof(simple_data_buffer)/sizeof(simple_data_buffer[0]), buf.offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(simple_data_buffer,buf.buffer, buf.offset);
}
