#include "tlv.h"
#include "name.h"

int8_t tlfield_decode_name(buffer_read_t *in, ndn_name_t *name)
{
    int8_t result = -1;

    if (in) {
        tlfield_t field;

        result = -2;
        /** read type field */
        if ((result = tlfield_decode(in, &field)) != 0) {
            return result;
        }

        /** check if the field is actually a 'name' tlv */
        result = -3;
        if (field != tlv_name) {
            return result;
        }

        result = -4;
        /** read length field */
        if ((result = tlfield_decode(in, &field)) != 0) {
            return result;
        }

        result = -5;

        /** save current offset */
        size_t start = in->offset;
        size_t length = field;
        size_t i = 0;

        /** TODO: check! */
        while (in->offset < (start + length)) {
            /** overflow? */
            if (i >= NDN_NAME_COMPONENTS_SIZE) {
                result = -6;
                return result;
            }
            
            /** retrieve component */
            if ((result = tlfield_decode_name_component(in, &(name->components[i]))) != 0) {
                return result;
            }
        }

        result = 0;
        name->components_size = i;
    }

    return result;
}
