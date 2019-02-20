#include <stdio.h>
#include "tlv.h"
#include "buffer.h"

int8_t tlfield_encode(buffer_write_t *out, tlfield_t field)
{
    int8_t result = -1;

    size_t remaining = buffer_remaining(out);

    if (field < 253) {
        result = buffer_write(out, (uint8_t)field);
    }
    else if (field < (1UL << 16)) {
        if (remaining >= 3) {
            buffer_write(out, (uint8_t)253);
            buffer_write(out, (uint8_t)((field & 0xFF00UL) >> 8));
            buffer_write(out, (uint8_t)((field & 0x00FFUL) >> 0));
            result = 0;
        }
    }
    else if (field < (1UL << 32)) {
        if (remaining >= 5) {
            buffer_write(out, (uint8_t)254);
            buffer_write(out, (uint8_t)((field & 0xFF000000UL) >> 24));
            buffer_write(out, (uint8_t)((field & 0x00FF0000UL) >> 16));
            buffer_write(out, (uint8_t)((field & 0x0000FF00UL) >> 8));
            buffer_write(out, (uint8_t)((field & 0x000000FFUL) >> 0));
            result = 0;
        }
    }
#ifdef NDNUP_64BIT
    else if (field < (1UL << 64)) {
        if (remaining >= 9) {
            buffer_write(out, (uint8_t)255);
            buffer_write(out, (uint8_t)((field & 0xFF00000000000000UL) >> 56));
            buffer_write(out, (uint8_t)((field & 0x00FF000000000000UL) >> 48));
            buffer_write(out, (uint8_t)((field & 0x0000FF0000000000UL) >> 40));
            buffer_write(out, (uint8_t)((field & 0x000000FF00000000UL) >> 32));
            buffer_write(out, (uint8_t)((field & 0x00000000FF000000UL) >> 24));
            buffer_write(out, (uint8_t)((field & 0x0000000000FF0000UL) >> 16));
            buffer_write(out, (uint8_t)((field & 0x000000000000FF00UL) >> 8));
            buffer_write(out, (uint8_t)((field & 0x00000000000000FFUL) >> 0));
            result = 0;
        }
    }
#endif

    return result;
}

int8_t nonnegative_int_encode(buffer_write_t *out, uint32_t value)
{
    int8_t result = 0;

    if (value > 0x0000FFFF) {
        buffer_write(out, (value & 0xFF000000) >> 24);
        buffer_write(out, (value & 0x00FF0000) >> 16);
    }
    if (value > 0x000000FF) {
        buffer_write(out, (value & 0x0000FF00) >> 8);
    }
    buffer_write(out, (value & 0x000000FF) >> 0);

    return result;
}
