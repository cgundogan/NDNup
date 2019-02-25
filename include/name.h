/*
 * Copyright (C) 2019 Safety IO
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        component.h
 * @brief       Definitions for NDN names
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef NAME_H
#define NAME_H

#include <stdint.h>
#include <stdlib.h>

#include "tlv.h"
#include "helper.h"
#include "constants.h"
#include "component.h"
#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief NDN name
 * (This structure is memory expensive so please be careful when using it.)
 * @{
 */
typedef struct {
  /**
   * The array of name components contained in this name (not including T and L)
   */
  ndn_component_t components[NDN_NAME_COMPONENTS_SIZE];
  /**
   * The number of name components
   */
  uint32_t components_size;
} ndn_name_t;
/** @} */

/**
 * @brief       Returns the size of an encoded Name TLV
 *
 * @param[in]   name     Name to calculate the length of
 * @return      encoded name length in bytes
 */
size_t get_name_block_size(const ndn_name_t* name);

/**
 * @brief       Encodes a Name
 *
 * @param[out]  out      output buffer
 * @param[in]   name     Name to encode
 * @retval      0 on succes
 */
int8_t name_encode(buffer_write_t *out, const ndn_name_t *name);

int8_t tlfield_decode_name(buffer_read_t *in, ndn_name_t *name);

#ifdef __cplusplus
}
#endif

#endif /* NAME_H */

/**
 * @}
 */
