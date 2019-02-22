#include "interest.h"
#include "tlv.h"


int8_t interest_decode(ndn_interest_t *interest, buffer_read_t *in)
{
    int8_t result = -1;

    if (interest) {
        result = -2;

        if (in) {
            /** initalize interest with default values */
            interest_create(interest);

            tlfield_t field = 0;
            /** if reading the type of the first type-length field was successful */
            if ((result = tlfield_decode(in, &field)) == 0) {
                result = -3;

                /** check if the buffer actually contains an interest */
                if (field == tlv_interest) {
                    /** read the length of the interest */
                    tlfield_decode(in, &field);
                    tlfield_t max_offset = in->offset + field;

                    /** read the name of the interest */
                    if ((result = tlfield_decode_name(in, &(interest->name))) == -1) {
                        return result;
                    }

                    /** read the remaining fields */
                    while (in->offset < max_offset) {
                        /** read type */
                        if((result = tlfield_decode(in, &field)) != 0) {
                            /** todo */
                            return result;
                        }

                        // TODO: add error handling

                        if (field == tlv_nonce) {
                            tlv_nonnegative_int_decode(in, (uint64_t *)&(interest->nonce));
                        }
                        else if (field == tlv_must_be_fresh) {
                            /** read length */
                            tlfield_decode(in, &field);
                            interest->must_be_fresh_enabled = 1;
                        }
                        else if (field == tlv_can_be_prefix) {
                            /** read length */
                            tlfield_decode(in, &field);
                            interest->can_be_prefix_enabled = 1;
                        }
                        else if (field == tlv_hop_limit) {
                            tlv_nonnegative_int_decode(in, (uint64_t *)&(interest->hop_limit));
                            interest->hop_limit_enabled = 1;
                        }
                        else if (field == tlv_interest_lifetime) {
                            tlv_nonnegative_int_decode(in, (uint64_t *)&(interest->lifetime));
                            interest->lifetime_enabled = 1;
                        }
                        else {
                            /* TODO */
                            return -1;
                        }
                    }
                }
            }

            result = 0;

            return result;
        }
    }

    return result;
}
