#include "tlv.h"
#include "data.h"
#include "name.h"

static size_t metainfo_length(const ndn_data_t *data)
{
    size_t length = 0;

    if (data->contenttype_enabled) {
        length += 2 + nonnegative_int_length(data->metainfo.contenttype);
    }

    if (data->freshnessperiod_enabled) {
        length += 2 + nonnegative_int_length(data->metainfo.freshnessperiod);
    }

    if (data->freshnessperiod_enabled) {
        /* TODO */
    }

    return length;
}

static int8_t metainfo_encode(buffer_write_t *out, const ndn_data_t *data)
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

size_t get_data_size(const ndn_data_t* data)
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

int8_t data_encode(buffer_write_t *out, ndn_data_t *data)
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
