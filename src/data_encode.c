#include "tlv.h"
#include "data.h"
#include "name.h"

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
                if (data->contenttype_enabled) {
                    tlv_nonnegative_int_encode(out, tlv_content_type, data->metainfo.contenttype);
                }
                if (data->freshnessperiod_enabled) {
                    tlv_nonnegative_int_encode(out, tlv_freshness_period, data->metainfo.freshnessperiod);
                }
                if (data->finalblockid_enabled) {
                    /* TODO */
                }
            }
            result = 0;
        }
    }

    return result;
}
