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

/**
 * @brief       Buffer representation
 * @{
 */
typedef struct {
    uint8_t *buffer; /**< Pointer to the actual buffer */
    size_t length;   /**< Maximum length of the buffer */
    size_t offset;   /**< Current read/write offset within the buffer */
} ndnup_buffer_t;
/** @} */

/**
 * @brief       Buffer for reading
 */
typedef ndnup_buffer_t ndnup_buffer_read_t;

/**
 * @brief       Buffer for writing
 */
typedef ndnup_buffer_t ndnup_buffer_write_t;

/**
 * @brief       Initializes a ndnup_buffer_t
 *
 * @param[in,out]  nbuf         ndnbuf_buffer_t to initialize
 * @param[in]      buffer       Pointer to the actual buffer
 * @param[in]      buffer_len   Actual length of @p buffer
 */
static inline void ndnup_buffer_init(ndnup_buffer_t *nbuf, uint8_t *buffer, size_t buffer_len)
{
    nbuf->buffer = buffer;
    nbuf->length = buffer_len;
    nbuf->offset = 0;
    return;
}

/**
 * @brief           Returns the remaining bytes in @p nbuf
 * @param[in,out]   nbuf         Buffer to calculate remaining bytes from
 * @return          Remaining bytes in the buffer of @p nbuf
 */
static inline size_t ndnup_buffer_remaining(const ndnup_buffer_t *nbuf)
{
    return (nbuf->length - nbuf->offset);
}

/**
 * @brief       Reads from @p nbuf into @p out and advances ndnup_buffer_read_t::offset.
 *
 * @param[in,out]   nbuf         Buffer to read from
 * @param[out]      out          Store read byte into @p out
 * @retval          0 on success
 * @retval          -1 on end of buffer
 */
int8_t ndnup_buffer_read(ndnup_buffer_read_t *nbuf, uint8_t *out);

/**
 * @brief       Writes @p in into @p nbuf and advances ndnup_buffer_write_t::offset.
 *
 * @param[in,out] nbuf         Buffer to write into
 * @param[in]     in           Value to write into @p nbuf
 * @retval        0 on success
 * @retval        -1 on end of buffer
 */
int8_t ndnup_buffer_write(ndnup_buffer_write_t *nbuf, uint8_t in);

/**
 * @brief       Writes @p block in @p nbuf and advances ndnup_buffer_write_t::offset by @p block_len.
 *
 * @param[in,out] nbuf         Buffer to write into
 * @param[in]     block        Block to write to @p nbuf
 * @retval        0 on success
 * @retval        -1 on end of buffer
 */
int8_t ndnup_buffer_write_block(ndnup_buffer_write_t *nbuf, uint8_t *block, size_t block_len);

/**
 * @brief       Reads a block from @p nbuf into @p block and advances ndnup_buffer_read_t::offset by @p block_len.
 *
 * @param[in,out]   nbuf         Buffer to read from
 * @param[out]      block        Store read block to @p block
 * @retval          0 on success
 * @retval          -1 on end of buffer
 */
int8_t ndnup_buffer_read_block(ndnup_buffer_read_t *nbuf, uint8_t *block, size_t block_len);

#endif /* NDNUP_BUFFER_H */

/**
 * @}
 */
