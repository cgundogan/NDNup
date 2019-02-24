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
#ifdef NDNUP_64BIT
    else if (field < (1UL << 32)) {
#else
    else {
#endif
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
    else {
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

int8_t tlv_nonnegative_int_encode(buffer_write_t *out, tlfield_t type, uint32_t value)
{
    int8_t result = 0;

    tlfield_encode(out, type);
    tlfield_encode(out, tlv_nonnegative_int_length(value));

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

size_t tlv_nonnegative_int_length(uint32_t value)
{
    if (value <= 0x000000FF) {
        return 1;
    }
    else if (value <= 0x0000FFFF) {
        return 2;
    }
    else if (value <= 0xFFFFFFFF) {
        return 4;
    }
    return 8;
}

int8_t tlv_boolean_encode(buffer_write_t *out, tlfield_t type)
{
    tlfield_encode(out, type);
    tlfield_encode(out, 0);

    return 0;
}

int8_t tlfield_decode(buffer_read_t *in, tlfield_t *field)
{
    int8_t result = -1;
    tlfield_t tlfield = 0;

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

int8_t tlv_nonnegative_int_decode(buffer_read_t *in, uint64_t *value)
{
    int8_t result = -1;

    if (in) {
        result = -2;

        if (value) {
            result = -3;
            tlfield_t length;

            tlfield_decode(in, &length);

            if (((length & (length - 1)) == 0) && length <= 8) {
                result = 0;

                do {
                    uint64_t tmp = 0;
                    buffer_read(in, (uint8_t *)&tmp);
                    *value += tmp << ((length - 1) * 8);
                } while (--length);
            }
        }
    }

    return result;
}
