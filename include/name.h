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

#include <stdint.h>

#include "constants.h"
#include "component.h"

#ifndef NAME_H 
#define NAME_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The structure to represent the Name.
 * This structure is memory expensive so please be careful when using it.
 */
typedef struct ndn_name {
  /**
   * The array of name components contained in this name (not including T and L)
   */
  ndn_component_t components[NDN_NAME_COMPONENTS_SIZE];
  /**
   * The number of name components
   */
  uint32_t components_size;
} ndn_name_t;


static size_t get_name_block_size(const ndn_name_t* name)
{
    size_t result = 0;

    for (uint32_t i = 0; i < name->components_size; i++) {
        result += get_component_block_size(&(name->components[i]));
    }

    return result;
};

#ifdef __cplusplus
}
#endif

#endif 
