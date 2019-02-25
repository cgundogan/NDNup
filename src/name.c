#include "ndnv03/tlv.h"
#include "ndnv03/name.h"
#include "ndnv03/component.h"

size_t get_component_block_size(const ndn_component_t *component)
{
    return get_block_size(component->type, component->size);
}

size_t get_name_block_size(const ndn_name_t* name)
{
    size_t result = 0;

    for (uint32_t i = 0; i < name->components_size; i++) {
        result += get_component_block_size(&(name->components[i]));
    }

    return get_block_size(tlv_name, result);
}

int8_t name_encode(buffer_write_t *out, const ndn_name_t *name)
{
    tlfield_encode(out, tlv_name);
    tlfield_encode(out, get_name_block_size(name) - 2);

    for (uint32_t i = 0; i < name->components_size; i++) {
        ndn_component_t *comp = (ndn_component_t *) &(name->components[i]);
        tlfield_encode(out, comp->type);
        tlfield_encode(out, comp->size);
        buffer_write_block(out, comp->value, comp->size);
    }

    return 0;
}

int8_t tlfield_decode_name(buffer_read_t *in, ndn_name_t *name)
{
    int8_t result = -1;

    if (in) {
        tlfield_t field = 0;

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
            i++;
        }

        result = 0;
        name->components_size = i;
    }

    return result;
}

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
        /** FIXME: check */
        result = buffer_read_block(in, component->value, component->size);
    }

    return result;
}
