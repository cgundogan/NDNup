#include "tlv.h"
#include "interest.h"
#include "name.h"

int8_t nonce_encode(buffer_write_t *out, uint32_t nonce)
{
    /* TODO add error checking */
    int8_t result = 0;

    tlfield_encode(out, tlv_nonce);
    tlfield_encode(out, 4);
    buffer_write(out, (nonce & 0xFF000000) >> 24);
    buffer_write(out, (nonce & 0x00FF0000) >> 16);
    buffer_write(out, (nonce & 0x0000FF00) >> 8);
    buffer_write(out, (nonce & 0x000000FF) >> 0);

    return result;
}

int8_t interest_lifetime_encode(buffer_write_t *out, uint32_t interest_lifetime)
{
    /* TODO add error checking */
    int8_t result = 0;
    uint8_t lifetime_len = get_nonnegative_int_size(interest_lifetime);

    tlfield_encode(out, tlv_interest_lifetime);
    tlfield_encode(out, lifetime_len);
    nonnegative_int_encode(out, interest_lifetime);

    return 0;
}

int8_t interest_encode(buffer_write_t *out, ndn_interest_t *interest)
{
    int8_t result = -1;

    if (out) {
        result = -2;

        if (interest) {
            int size = get_interest_size(interest);

            /* write outer TLV */
            tlfield_encode(out, tlv_interest);
            /* write length */
            tlfield_encode(out, size);
            /* write value */

            /* write name */
            name_encode(out, (const ndn_name_t *)&interest->name);

            /* write 'can be prefix' */
            if (interest->can_be_prefix_enabled) {
                tlfield_encode(out, tlv_can_be_prefix);
                tlfield_encode(out, 0);
            }

            /* write 'must be fresh' */
            if (interest->must_be_fresh_enabled) {
                tlfield_encode(out, tlv_must_be_fresh);
                tlfield_encode(out, 0);
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
