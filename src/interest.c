#include "ndnv03/tlv.h"
#include "ndnv03/interest.h"
#include "ndnv03/name.h"

int8_t nonce_encode(buffer_write_t *out, uint32_t nonce)
{
    int8_t result = -1;

    if (out) {
        /* TODO add error checking */
        tlfield_encode(out, tlv_nonce);
        tlfield_encode(out, 4);
        buffer_write(out, (nonce & 0xFF000000) >> 24);
        buffer_write(out, (nonce & 0x00FF0000) >> 16);
        buffer_write(out, (nonce & 0x0000FF00) >> 8);
        buffer_write(out, (nonce & 0x000000FF) >> 0);

        result = 0;
    }

    return result;
}

int8_t interest_lifetime_encode(buffer_write_t *out, uint32_t interest_lifetime)
{
    int8_t result = -1;

    if (out) {
        /* TODO add error checking */

        tlv_nonnegative_int_encode(out, tlv_interest_lifetime, interest_lifetime);

        result = 0;
    }

    return result;
}

size_t interest_get_size(const ndnv03_interest_t* interest)
{
    size_t size = get_name_block_size(&(interest->name));

    if (interest->can_be_prefix_enabled) {
        size += 2;
    }

    if (interest->must_be_fresh_enabled){
        size += 2;
    }

    if (interest->hop_limit_enabled) {
        size += 3;
    }

    if (interest->parameters_enabled) {
        size += get_block_size(tlv_parameters, interest->parameters.size);
    }

    /** size of nonce */
    size += 6;

    if (interest->lifetime_enabled) {
        /** size of lifetime */
        size += 2 + tlv_nonnegative_int_length(interest->lifetime);
    }

    return size;
}

int8_t interest_encode(buffer_write_t *out, ndnv03_interest_t *interest)
{
    int8_t result = -1;

    if (out) {
        result = -2;

        if (interest) {
            int size = interest_get_size(interest);

            /* write outer TLV */
            tlfield_encode(out, tlv_interest);
            /* write length */
            tlfield_encode(out, size);

            /* write name */
            name_encode(out, (const ndn_name_t *)&interest->name);

            /* write 'can be prefix' */
            if (interest->can_be_prefix_enabled) {
                tlv_boolean_encode(out, tlv_can_be_prefix);
            }

            /* write 'must be fresh' */
            if (interest->must_be_fresh_enabled) {
                tlv_boolean_encode(out, tlv_must_be_fresh);
            }

            /* write nonce */
            nonce_encode(out, interest->nonce);

            /* write interest lifetime */
            if (interest->lifetime_enabled) {
                interest_lifetime_encode(out, interest->lifetime);
            }

            /* write hop limit */
            if (interest->hop_limit_enabled) {
                tlfield_encode(out, tlv_hop_limit);
                tlfield_encode(out, 1);
                buffer_write(out, interest->hop_limit);
            }

            /* write parameters */
            if (interest->parameters_enabled) {
                tlfield_encode(out, tlv_parameters);
                tlfield_encode(out, interest->parameters.size);

            }

            result = 0;
        }
    }

    return result;
}

int8_t interest_decode(ndnv03_interest_t *interest, buffer_read_t *in)
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
