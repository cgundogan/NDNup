/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        ndnup.h
 * @brief       NDNup functions
 * @author      Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef NDNUP_H
#define NDNUP_H

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Type definition for `TLV-Type` and `TLV-Length` fields
 */
typedef uint32_t ndnup_tlfield;

/**
 * @brief       Encodes a TLV field
 *
 * @param[out]  out     output buffer
 * @param[in]   field   number to encode
 * @return      Number of bytes written to @p out
 * @retval      0 on error
 */
size_t ndnup_encode_tlfield(uint8_t *out, ndnup_tlfield field);

#endif /* NDNUP_H */

/**
 * @}
 */
