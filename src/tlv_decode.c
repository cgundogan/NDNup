#include <stdio.h>
#include "tlv.h"
#include "ndnup_buffer.h"

int8_t tlfield_decode(ndnup_buffer_read_t *in, tlfield_t *field)
{
    int8_t result = -1;
    tlfield_t tlfield;

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
