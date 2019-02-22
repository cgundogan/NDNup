#include "data.h"
#include "tlv.h"

int8_t metainfo_decode(ndn_data_t *data, buffer_read_t *in)
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

int8_t content_decode(ndn_data_content_t *content, buffer_read_t *in)
{
    tlfield_t length = 0;
    tlfield_decode(in, &length);
    content->length = length;
    buffer_read_block(in, (uint8_t *)content->value, length);

   return 0;
}

int8_t data_decode(ndn_data_t *data, buffer_read_t *in)
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
