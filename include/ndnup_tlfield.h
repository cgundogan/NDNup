/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        ndnup_tlfield.h
 * @brief       NDNup functions to handle TLV encoding and decoding
 * @author      Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright   MIT License
 * @addtogroup  NDNup
 * @{
 */

#ifndef NDNUP_TLFIELD_H
#define NDNUP_TLFIELD_H

#include <stdio.h>
#include <stdint.h>

#include "ndnup_buffer.h"

/**
 * @brief Type definition for `TLV-Type` and `TLV-Length` fields
 */
typedef uint32_t ndnup_tlfield_t;

/**
 * @brief       Encodes a TLV field
 *
 * @param[out]  out     output buffer
 * @param[in]   field   number to encode
 * @return      Number of bytes written to @p out
 * @retval      0 on succes
 */
int8_t ndnup_encode_tlfield(ndnup_buffer_write_t *out, ndnup_tlfield_t field);

/**
 * @brief       Decodes a TLV field
 *
 * @param[in]   in     buffer to read from
 * @param[out]  field  decoded TLV field
 * @retval      0 on success
 */
int8_t ndnup_decode_tlfield(ndnup_buffer_read_t *in, ndnup_tlfield_t *field);

#endif /* NDNUP_TLFFIELD_H */

/**
 * @}
 */
