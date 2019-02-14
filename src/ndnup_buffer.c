#include <stdio.h>
#include "ndnup_buffer.h"

int8_t ndnup_buffer_read(ndnup_buffer_t *nbuf, uint8_t *out)
{
    uint8_t result;

    if (nbuf->offset >= nbuf->length) {
        return -1;
    }

    result = nbuf->buffer[nbuf->offset++];

    *out = result;

    return 0;
}

