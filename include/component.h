/*
 * Copyright (C) 2019 Safety IO 
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        component.h
 * @brief       Data structures and functions for NDN name components
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include <limits.h>
#include <stdint.h>

#include "constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDN_INVALID_COMPONENT
#define NDN_INVALID_COMPONENT                    0u /**< invalid name component type */ 
#endif 

#ifndef NDN_IMPLICIT_SHA256_DIGEST_COMPONENT
#define NDN_IMPLICIT_SHA256_DIGEST_COMPONENT     1u /**< implicit SHA-256 digest component */
#endif 

#ifndef NDN_PARAMETERS_SHA256_DIGEST_COMPONENT
#define NDN_PARAMETERS_SHA256_DIGEST_COMPONENT	 2u /**< SHA-256 digest of Interest Parameters */	
#endif 

#ifndef NDN_GENERIC_NAME_COMPONENT
#define NDN_GENERIC_NAME_COMPONENT               8u /**< generic name component */	
#endif 

#ifndef NDN_KEYWORD_NAME_COMPONENT
#define NDN_KEYWORD_NAME_COMPONENT              32u /**< well-known keyword */ 
#endif 

#ifndef NDN_SEGMENT_NAME_COMPONENT
#define NDN_SEGMENT_NAME_COMPONENT              33u /**< segment number */	
#endif 

#ifndef NDN_BYTE_OFFSET_NAME_COMPONENT
#define NDN_BYTE_OFFSET_NAME_COMPONENT		    34u /**< byte offset	*/
#endif 

#ifndef NDN_VERSION_NAME_COMPONENT
#define NDN_VERSION_NAME_COMPONENT              35u /**< version number */ 
#endif 

#ifndef NDN_TIMESTAMP_NAME_COMPONENT
#define NDN_TIMESTAMP_NAME_COMPONENT            36u /**< unix timestamp in microseconds */ 
#endif 

#ifndef NDN_SEQUENCE_NUM_NAME_COMPONENT
#define NDN_SEQUENCE_NUM_NAME_COMPONENT         37u /**< sequence number */
#endif 

/**
 *
 */
typedef struct ndn_component {
   ndnup_tlfield_t type;                          /**< the type of the component */
   uint8_t value[NDN_NAME_COMPONENT_BUFFER_SIZE]; /**< the actual value the component holds */
   uint32_t size;                                 /**< the actual size of the component buffer */
} ndn_component_t;

static size_t get_component_block_size(ndn_component_t *component)
{
    size_t result = 0;
    // FIXME
    return result;
};

#ifdef __cplusplus
}
#endif

#endif /* COMPONENT_H */

/**
 * @}
 */
