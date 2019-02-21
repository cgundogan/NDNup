#include "data.h"
#include "tlv.h"

int8_t data_decode(ndn_data_t *data, buffer_read_t *in)
{
    int8_t result = -1;

    if (data) {
        result = -2;

        if (in) {
            /** initalize data with default values */
            data_create(data);

            tlfield_t field;
            /** if reading the type of the first type-length field was successful */
            if ((result = tlfield_decode(in, &field)) == 0) {
                result = -3;

                /** check if the buffer actually contains an interest */
                if (field == tlv_data) {
                    /** read the length of the data */
                    uint32_t length = tlfield_decode(in, &field);

                    /** read the name */
                //    tlfield_decode(in, &field);


                }
            }

            return result;
        }
    }

    return result;
}
