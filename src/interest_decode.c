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

            tlfield_t field;
            /** if reading the type of the first type-length field was successful */
            if ((result = tlfield_decode(in, &field)) == 0) {
                result = -3;

                /** check if the buffer actually contains an interest */
                if (field == tlv_interest) {
                    /** read the length of the interest */ 
                    uint32_t length = tlfield_decode(in, &field);

                    /** read the name of the interest */
                //    tlfield_decode(in, &field);
                    
                
                }
            }

            return result;
        }
    }

    return result;
}




