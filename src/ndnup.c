#include <stdio.h>
#include "ndnup.h"

size_t ndnup_encode_tlfield(uint8_t *out, ndnup_tlfield field)
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
