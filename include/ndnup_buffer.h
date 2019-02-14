/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        ndnup_buffer.h
 * @brief       NDNup-Buffer functions to handle NDNup-Buffers
 * @author      Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright   MIT License
 * @addtogroup  NDNup-Buffer
 * @{
 */

#ifndef NDNUP_BUFFER_H
#define NDNUP_BUFFER_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    size_t length;
    size_t offset;
} ndnup_buffer_t;

/**
 * @brief       Initializes a ndnup_buffer_t
 *
 * @param[out]  nbuf         ndnbuf_buffer_t to initialize
 * @param[in]   buffer       Pointer to the actual buffer
 * @param[in]   buffer_len   Actual length of @p buffer
 */
static inline void ndnup_buffer_init(ndnup_buffer_t *nbuf, uint8_t *buffer, size_t buffer_len)
{
    nbuf->buffer = buffer;
    nbuf->length = buffer_len;
    nbuf->offset = 0;
    return;
}

/**
 * @brief       Returns the remaining bytes in @p nbuf
 * @param[in]   nbuf         Buffer to calculate remaining bytes from
 * @return      Remaining bytes in the buffer of @p nbuf
 */
static inline size_t ndnup_buffer_read_remaining(ndnup_buffer_t *nbuf)
{
    return (nbuf->length - nbuf->offset);
}

/**
 * @brief       Reads from the buffer into @p out and advances ndnup_buffer_t::offset.
 *
 * @param[in]   nbuf         Buffer to read from
 * @param[out]  out          Store read byte into @p out
 */
int8_t ndnup_buffer_read(ndnup_buffer_t *nbuf, uint8_t *out);

#endif /* NDNUP_BUFFER_H */

/**
 * @}
 */
