#include <stdio.h>
#include "ndnup_tlfield.h"
#include "ndnup_buffer.h"

int8_t ndnup_encode_tlfield(ndnup_buffer_write_t *out, ndnup_tlfield_t field)
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

int8_t ndnup_decode_tlfield(ndnup_buffer_read_t *in, ndnup_tlfield_t *field)
{
    int8_t result = -1;
    ndnup_tlfield_t tlfield;

    if (0 > ndnup_buffer_read(in, (uint8_t *)&tlfield)) {
        return -1;
    }

    size_t remaining = ndnup_buffer_remaining(in);

    if (tlfield < 253) {
        *field = tlfield;
        result = 0;
    }
    else if (tlfield == 253) {
        if (remaining >= 2) {
            uint8_t tmp;
            tlfield = 0;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 8;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 0;

            *field = tlfield;

            result = 0;
        }
    }
    else if (tlfield == 254) {
        if (remaining >= 4) {
            uint8_t tmp;
            tlfield = 0;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 24;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 16;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 8;

            ndnup_buffer_read(in, &tmp);
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

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 56;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 48;

            ndnup_buffer_read(in, &tmp2);
            tlfield |= tmp << 40;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 32;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 24;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 16;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 8;

            ndnup_buffer_read(in, &tmp);
            tlfield |= tmp << 0;

            *field = tlfield;

            result = 0;
        }
    }
#endif

    return result;
}
