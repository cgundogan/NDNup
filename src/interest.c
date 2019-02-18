#include "tlv.h"
#include "ndnup_tlfield.h"
#include "interest.h"


int8_t interest_encode(ndnup_buffer_write_t *out, ndn_interest_t *interest)
{
    int8_t result = -1;

    if (out) {
        result = -2; 

        if (interest) {
            /* FIXME */
            int size = 1;

            /* write outer TLV */
            ndnup_tlfield_encode(out, tlv_interest);
            /* write length */
            ndnup_tlfield_encode(out, size);
            /* write value */

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
            ndnup_tlfield_encode(out, tlv_nonce);
            ndnup_tlfield_encode(out, 4);


            /** write interest lifetime */ 
            ndnup_tlfield_encode(out, tlv_interest_lifetime);
            ndnup_tlfield_encode(out, 2);


            /** write hop limit */ 
            if (interest->hop_limit_enabled) {
                ndnup_tlfield_encode(out, tlv_hop_limit);
                ndnup_tlfield_encode(out, 1);

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
