#include <stdio.h>

#include "tlv.h"
#include "buffer.h"

int8_t tlfield_decode(buffer_read_t *in, tlfield_t *field)
{
    int8_t result = -1;
    tlfield_t tlfield;

    if (0 > buffer_read(in, (uint8_t *)&tlfield)) {
        return -1;
    }

    size_t remaining = buffer_remaining(in);

    if (tlfield < 253) {
        *field = tlfield;
        result = 0;
    }
    else if (tlfield == 253) {
        if (remaining >= 2) {
            uint8_t tmp;
            tlfield = 0;

            buffer_read(in, &tmp);
            tlfield |= tmp << 8;

            buffer_read(in, &tmp);
            tlfield |= tmp << 0;

            *field = tlfield;

            result = 0;
        }
    }
    else if (tlfield == 254) {
        if (remaining >= 4) {
            uint8_t tmp;
            tlfield = 0;

            buffer_read(in, &tmp);
            tlfield |= tmp << 24;

            buffer_read(in, &tmp);
            tlfield |= tmp << 16;

            buffer_read(in, &tmp);
            tlfield |= tmp << 8;

            buffer_read(in, &tmp);
            tlfield |= tmp << 0;

            *field = tlfield;

            result = 0;
        }
    }
#ifdef NDN_64BIT
    else if (tlfield == 255) {
        if (remaining >= 8) {
            uint8_t tmp;
            tlfield = 0;

            buffer_read(in, &tmp);
            tlfield |= tmp << 56;

            buffer_read(in, &tmp);
            tlfield |= tmp << 48;

            buffer_read(in, &tmp2);
            tlfield |= tmp << 40;

            buffer_read(in, &tmp);
            tlfield |= tmp << 32;

            buffer_read(in, &tmp);
            tlfield |= tmp << 24;

            buffer_read(in, &tmp);
            tlfield |= tmp << 16;

            buffer_read(in, &tmp);
            tlfield |= tmp << 8;

            buffer_read(in, &tmp);
            tlfield |= tmp << 0;

            *field = tlfield;

            result = 0;
        }
    }
#endif

    return result;
}

int8_t uint16_decode(buffer_read_t *in, uint16_t *value)
{
    int8_t result = -1;

    if (in) {
        result = -2;

        if (value) {
            result = -3;

            if ((in->offset + 2) <= in->length) {
                result = 0;

                *value = ((uint16_t)in->buffer[in->offset] << 8) +
                    in->buffer[in->offset+1]; 

                in->offset += 2;
            }
        }
    }

    return result;
}

