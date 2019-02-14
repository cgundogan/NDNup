#include <stdio.h>
#include "ndnup_tlfield.h"
#include "ndnup_buffer.h"

size_t ndnup_encode_tlfield(uint8_t *out, ndnup_tlfield_t field)
{
    size_t offset = 0;

    if (field < 253) {
        *out = field;
        offset = 1;
    }
    else if (field < (1UL << 16)) {
        *out = 253;
        offset = 3;
        out[1] = (field & 0xFF00UL) >> 8;
        out[2] = (field & 0x00FFUL) >> 0;
    }
    else if (field < (1UL << 32)) {
        *out = 254;
        offset = 5;
        out[1] = (field & 0xFF000000UL) >> 24;
        out[2] = (field & 0x00FF0000UL) >> 16;
        out[3] = (field & 0x0000FF00UL) >> 8;
        out[4] = (field & 0x000000FFUL) >> 0;
    }
#ifdef NDNUP_64BIT
    else if (field < (1UL << 64)) {
        *out = 255;
        offset = 9;
        out[1] = field & (0xFF00000000000000) >> 56;
        out[2] = field & (0x00FF000000000000) >> 48;
        out[3] = field & (0x0000FF0000000000) >> 40;
        out[4] = field & (0x000000FF00000000) >> 32;
        out[5] = field & (0x00000000FF000000) >> 24;
        out[6] = field & (0x0000000000FF0000) >> 16;
        out[7] = field & (0x000000000000FF00) >> 8;
        out[8] = field & (0x00000000000000FF) >> 0;
    }
#endif

    return offset;
}

int8_t ndnup_decode_tlfield(ndnup_buffer_t *in, ndnup_tlfield_t *field)
{
    int8_t result = 0;
    uint8_t tmp, tmp2;

    if (0 > ndnup_buffer_read(in, &tmp)) {
        return -1;
    }

    size_t remaining = ndnup_buffer_read_remaining(in);

    if (tmp < 253) {
        *field = tmp;
    }
    else if (tmp == 253) {
        if (remaining >= 2) {
            tmp = 0;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 8;

            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 0;

            *field = tmp;
        }
    }
    else if (tmp == 254) {
        if (remaining >= 4) {
            tmp = 0;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 24;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 16;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 8;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 0;

            *field = tmp;
        }
    }
#ifdef NDN_64BIT
    else if (tmp == 255) {
        if (remaining >= 8) {
            tmp = 0;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 56;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 48;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 40;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 32;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 24;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 16;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 8;
            ndnup_buffer_read(in, &tmp2);
            tmp |= tmp2 << 0;

            *field = tmp;
        }
    }
#endif

    return result;
}
