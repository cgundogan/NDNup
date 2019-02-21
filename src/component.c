#include "component.h"

int8_t tlfield_decode_name_component(buffer_read_t *in, ndn_component_t *component)
{
    int8_t result = -1;

    if (in) {
        tlfield_t field;

        result = -2;
        /** read type field */
        if ((result = tlfield_decode(in, &field)) != 0) {
            return result;
        }
        component->type = field;

        result = -3;
        /** read length field */
        if ((result = tlfield_decode(in, &field)) != 0) {
            return result;
        }

        result = -4;
        if (field > NDN_NAME_COMPONENT_BUFFER_SIZE) {
            return result;
        }

        component->size = field;


        result = 0;
    }

    return result;
}
