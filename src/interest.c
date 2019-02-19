#include "tlv.h"
#include "ndnup_tlfield.h"
#include "interest.h"
#include "name.h"

int8_t nonce_encode(ndnup_buffer_write_t *out, uint32_t nonce)
{
    /* TODO add error checking */
    int8_t result = 0;

    ndnup_tlfield_encode(out, tlv_nonce);
    ndnup_tlfield_encode(out, 4);
    ndnup_buffer_write(out, (nonce & 0xFF000000) >> 24);
    ndnup_buffer_write(out, (nonce & 0x00FF0000) >> 16);
    ndnup_buffer_write(out, (nonce & 0x0000FF00) >> 8);
    ndnup_buffer_write(out, (nonce & 0x000000FF) >> 0);

    return result;
}


int8_t interest_encode(ndnup_buffer_write_t *out, ndn_interest_t *interest)
{
    int8_t result = -1;

    if (out) {
        result = -2;

        if (interest) {
            int size = get_interest_size(interest);

            /* write outer TLV */
            ndnup_tlfield_encode(out, tlv_interest);
            /* write length */
            ndnup_tlfield_encode(out, size);
            /* write value */

            /* write name */
            name_encode(out, (const ndn_name_t *)&interest->name);

            /** write 'can be prefix' */
            if (interest->can_be_prefix_enabled) {
                ndnup_tlfield_encode(out, tlv_can_be_prefix);
                ndnup_tlfield_encode(out, 0);
            }

            /** write 'must be fresh' */
            if (interest->must_be_fresh_enabled) {
                ndnup_tlfield_encode(out, tlv_must_be_fresh);
                ndnup_tlfield_encode(out, 0);
            }

            /** write nonce */
            nonce_encode(out, interest->nonce);

            /** write interest lifetime */
            if (interest->lifetime_enabled) {
                ndnup_tlfield_encode(out, tlv_interest_lifetime);
                ndnup_tlfield_encode(out, 2);

            }


            /** write hop limit */
            if (interest->hop_limit_enabled) {
                ndnup_tlfield_encode(out, tlv_hop_limit);
                ndnup_tlfield_encode(out, 1);
                ndnup_buffer_write(out, interest->hop_limit);
            }

            /** write parameters */
            if (interest->parameters_enabled) {
                ndnup_tlfield_encode(out, tlv_parameters);
                ndnup_tlfield_encode(out, interest->parameters.size);

            }

            result = 0;
        }
    }

    return result;
}
