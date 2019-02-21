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

static ndn_data_t complex_data = {
    .name = {
        .components = {{.type = tlv_generic_name_component,
                        .size = 3,
                        .value = {'h', 'a', 'w'}},
                       {.type = tlv_generic_name_component,
                        .size = 3,
                        .value = {'m', 's', 'a'}}},
        .components_size = 2,
    },
    .metainfo = {
        .contenttype = 0x00,
        .freshnessperiod = 0x0000FFFF,
    },
    .content = {
        .value = { 0xFF, 0xFF },
        .length = 2,
    },
    .metainfo_enabled = 1,
    .contenttype_enabled = 1,
    .freshnessperiod_enabled = 1,
    .finalblockid_enabled = 0,
    .content_enabled = 1,
};
static uint8_t complex_data_buffer[] = {
    /* Outermost TLV */
    0x06, 0x19,
    /* Name */
    0x07, 0x0A,
    /* GenericNameComponent "haw" */
    0x08, 0x03, 0x68, 0x61, 0x77,
    /* GenericNameComponent "msa" */
    0x08, 0x03, 0x6d, 0x73, 0x61,
    /* MetaInfo TLV */
    0x14, 0x07,
    /* Content Type */
    0x18, 0x01, 0x00,
    /* FeshnessPeriod */
    0x19, 0x02, 0xFF, 0xFF,
    /* Content TLV */
    0x15, 0x02, 0xFF, 0xFF,
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

void test_data_encode_complex(void) {
    int8_t error = 0;
    buffer_write_t buf;

    buffer_init(&buf, buffer, sizeof(buffer) / sizeof(buffer[0]));

    error = data_encode(&buf, &complex_data);

    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(sizeof(complex_data_buffer)/sizeof(complex_data_buffer[0]), buf.offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(complex_data_buffer,buf.buffer, buf.offset);
}

void test_data_decode_simple(void) {
    int8_t error = 0;
    buffer_read_t buf;
    ndn_data_t data;

    buffer_init(&buf, simple_data_buffer, sizeof(simple_data_buffer) / sizeof(simple_data_buffer[0]));

    error = data_decode(&data, &buf);

    TEST_ASSERT_EQUAL_INT8(0, error);
    TEST_ASSERT_EQUAL_UINT(sizeof(simple_data_buffer)/sizeof(simple_data_buffer[0]), buf.offset);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(simple_data_buffer,buf.buffer, buf.offset);
    TEST_ASSERT_EQUAL_MEMORY(&simple_data, &data, sizeof(data));
}
