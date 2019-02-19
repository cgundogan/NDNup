#include <stdio.h>
#include "tlv.h"
#include "ndnup_buffer.h"

int8_t tlfield_encode(ndnup_buffer_write_t *out, tlfield_t field)
{
    int8_t result = -1;

    size_t remaining = ndnup_buffer_remaining(out);

    if (field < 253) {
        result = ndnup_buffer_write(out, (uint8_t)field);
    }
    else if (field < (1UL << 16)) {
        if (remaining >= 3) {
            ndnup_buffer_write(out, (uint8_t)253);
            ndnup_buffer_write(out, (uint8_t)((field & 0xFF00UL) >> 8));
            ndnup_buffer_write(out, (uint8_t)((field & 0x00FFUL) >> 0));
            result = 0;
        }
    }
    else if (field < (1UL << 32)) {
        if (remaining >= 5) {
            ndnup_buffer_write(out, (uint8_t)254);
            ndnup_buffer_write(out, (uint8_t)((field & 0xFF000000UL) >> 24));
            ndnup_buffer_write(out, (uint8_t)((field & 0x00FF0000UL) >> 16));
            ndnup_buffer_write(out, (uint8_t)((field & 0x0000FF00UL) >> 8));
            ndnup_buffer_write(out, (uint8_t)((field & 0x000000FFUL) >> 0));
            result = 0;
        }
    }
#ifdef NDNUP_64BIT
    else if (field < (1UL << 64)) {
        if (remaining >= 9) {
            ndnup_buffer_write(out, (uint8_t)255);
            ndnup_buffer_write(out, (uint8_t)((field & 0xFF00000000000000UL) >> 56));
            ndnup_buffer_write(out, (uint8_t)((field & 0x00FF000000000000UL) >> 48));
            ndnup_buffer_write(out, (uint8_t)((field & 0x0000FF0000000000UL) >> 40));
            ndnup_buffer_write(out, (uint8_t)((field & 0x000000FF00000000UL) >> 32));
            ndnup_buffer_write(out, (uint8_t)((field & 0x00000000FF000000UL) >> 24));
            ndnup_buffer_write(out, (uint8_t)((field & 0x0000000000FF0000UL) >> 16));
            ndnup_buffer_write(out, (uint8_t)((field & 0x000000000000FF00UL) >> 8));
            ndnup_buffer_write(out, (uint8_t)((field & 0x00000000000000FFUL) >> 0));
            result = 0;
        }
    }
#endif

    return result;
}
