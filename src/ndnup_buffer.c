#include <stdio.h>
#include "ndnup_buffer.h"

int8_t ndnup_buffer_read(ndnup_buffer_read_t *nbuf, uint8_t *out)
{
    uint8_t result;

    if (nbuf->offset >= nbuf->length) {
        return -1;
    }

    result = nbuf->buffer[nbuf->offset++];

    *out = result;

    return 0;
}

int8_t ndnup_buffer_write(ndnup_buffer_write_t *nbuf, uint8_t in)
{
    if (nbuf->offset >= nbuf->length) {
        return -1;
    }

    nbuf->buffer[nbuf->offset++] = in;

    return 0;
}

int8_t ndnup_buffer_read_block(ndnup_buffer_read_t *nbuf, uint8_t *block, size_t block_len)
{
    if ((nbuf->offset + block_len) >= nbuf->length) {
        return -1;
    }

    memcpy(block, (nbuf->buffer + nbuf->offset), block_len);
    nbuf->offset += block_len;

    return 0;
}

int8_t ndnup_buffer_write_block(ndnup_buffer_write_t *nbuf, uint8_t *block, size_t block_len)
{
    if ((nbuf->offset + block_len) >= nbuf->length) {
        return -1;
    }

    memcpy((nbuf->buffer + nbuf->offset), block, block_len);
    nbuf->offset += block_len;

    return 0;
}
