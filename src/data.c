#include "ndnv03/tlv.h"
#include "ndnv03/data.h"
#include "ndnv03/name.h"

static size_t metainfo_length(const ndnv03_data_t *data)
{
    size_t length = 0;

    if (data->contenttype_enabled) {
        length += 2 + tlv_nonnegative_int_length(data->metainfo.contenttype);
    }

    if (data->freshnessperiod_enabled) {
        length += 2 + tlv_nonnegative_int_length(data->metainfo.freshnessperiod);
    }

    if (data->freshnessperiod_enabled) {
        /* TODO */
    }

    return length;
}

static int8_t metainfo_encode(buffer_write_t *out, const ndnv03_data_t *data)
{
    int8_t result = 0;

    tlfield_encode(out, tlv_meta_info);
    tlfield_encode(out, metainfo_length(data));

    if (data->contenttype_enabled) {
        tlv_nonnegative_int_encode(out, tlv_content_type, data->metainfo.contenttype);
    }
    if (data->freshnessperiod_enabled) {
        tlv_nonnegative_int_encode(out, tlv_freshness_period, data->metainfo.freshnessperiod);
    }
    if (data->finalblockid_enabled) {
        /* TODO */
    }

    return result;
}

static int8_t content_encode(buffer_write_t *out, const ndn_data_content_t *content)
{
    tlfield_encode(out, tlv_content);
    tlfield_encode(out, content->length);
    buffer_write_block(out, (uint8_t *)content->value, content->length);

    return 0;
}

size_t get_data_size(const ndnv03_data_t* data)
{
    size_t size = get_name_block_size(&(data->name));
    if (data->metainfo_enabled) {
        size += 2 + metainfo_length(data);
    }
    if (data->content_enabled) {
        size += 2 + data->content.length;
    }
    return size;
}

int8_t data_encode(buffer_write_t *out, ndnv03_data_t *data)
{
    int8_t result = -1;

    if (out) {
        result = -2;

        if (data) {
            int size = get_data_size(data);

            /* write outer TLV */
            tlfield_encode(out, tlv_data);
            /* write length */
            tlfield_encode(out, size);

            /* write name */
            name_encode(out, (const ndn_name_t *)&data->name);

            if (data->metainfo_enabled) {
                metainfo_encode(out, data);
            }

            if (data->content_enabled) {
                content_encode(out, &data->content);
            }

            result = 0;
        }
    }

    return result;
}

static int8_t metainfo_decode(ndnv03_data_t *data, buffer_read_t *in)
{
    int8_t result = 0;
    tlfield_t length = 0;

    tlfield_decode(in, &length);
    size_t max_offset = in->offset + length;

    tlfield_t field = 0;

    while(in->offset < max_offset) {
        if ((result = tlfield_decode(in, &field)) != 0) {
            /* TODO */
            return result;
        }
        else if (field == tlv_content_type) {
            tlv_nonnegative_int_decode(in, (uint64_t *)&(data->metainfo.contenttype));
            data->contenttype_enabled = 1;
        }
        else if (field == tlv_freshness_period) {
            tlv_nonnegative_int_decode(in, (uint64_t *)&(data->metainfo.freshnessperiod));
            data->freshnessperiod_enabled = 1;
        }
        else if (field == tlv_final_block_id) {
            /* TODO */
            return -1;
        }
        else {
            /* TODO */
            return -1;
        }
    }

    return 0;
}

static int8_t content_decode(ndn_data_content_t *content, buffer_read_t *in)
{
    tlfield_t length = 0;
    tlfield_decode(in, &length);
    content->length = length;
    buffer_read_block(in, (uint8_t *)content->value, length);

   return 0;
}

int8_t data_decode(ndnv03_data_t *data, buffer_read_t *in)
{
    int8_t result = -1;

    if (data) {
        result = -2;

        if (in) {
            /** initalize data with default values */
            data_create(data);

            tlfield_t field = 0;
            /** if reading the type of the first type-length field was successful */
            if ((result = tlfield_decode(in, &field)) == 0) {
                result = -3;

                /** check if the buffer actually contains an data */
                if (field == tlv_data) {
                    /** read the length of the data */
                    tlfield_decode(in, &field);
                    tlfield_t max_offset = in->offset + field;

                    /** read the name */
                    if ((result = tlfield_decode_name(in, &(data->name))) == -1) {
                        return result;
                    }
                    while (in->offset < max_offset) {
                        if((result = tlfield_decode(in, &field)) != 0) {
                            /** todo */
                            return result;
                        }

                        if (field == tlv_meta_info) {
                            metainfo_decode(data, in);
                            data->metainfo_enabled = 1;
                        }

                        if (field == tlv_content) {
                            content_decode(&data->content, in);
                            data->content_enabled = 1;
                        }
                    }

                    result = 0;
                }
            }

            return result;
        }
    }

    return result;
}
