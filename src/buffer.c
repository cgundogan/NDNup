#include <stdio.h>
#include <string.h>

#include "ndnv03/buffer.h"

int8_t buffer_read(buffer_read_t *nbuf, uint8_t *out)
{
    uint8_t result;

    if (nbuf->offset > nbuf->length) {
        return -1;
    }

    result = nbuf->buffer[nbuf->offset++];

    *out = result;

    return 0;
}

int8_t buffer_write(buffer_write_t *nbuf, uint8_t in)
{
    if (nbuf->offset > nbuf->length) {
        return -1;
    }

    nbuf->buffer[nbuf->offset++] = in;

    return 0;
}

int8_t buffer_read_block(buffer_read_t *nbuf, uint8_t *block, size_t block_len)
{
    if ((nbuf->offset + block_len) > nbuf->length) {
        return -1;
    }

    memcpy(block, (nbuf->buffer + nbuf->offset), block_len);
    nbuf->offset += block_len;

    return 0;
}

int8_t buffer_write_block(buffer_write_t *nbuf, uint8_t *block, size_t block_len)
{
    if ((nbuf->offset + block_len) > nbuf->length) {
        return -1;
    }

    memcpy((nbuf->buffer + nbuf->offset), block, block_len);
    nbuf->offset += block_len;

    return 0;
}
