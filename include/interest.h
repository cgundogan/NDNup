/*
 * Copyright (C) 2019 Safety IO 
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        interest.h
 * @brief       Data structures and functions for NDN interests
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */


#include <stdint.h>

#include "name.h"
#include "constants.h"

#ifndef INTEREST_H 
#define INTEREST_H

#ifndef INTEREST_DEFAULT_LIFETIME
#define INTEREST_DEFAULT_LIFETIME (4000u)
#endif 

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The structure to represent the Interest parameters element.
 */
typedef struct interest_params {
  uint8_t value[NDN_INTEREST_PARAMS_BUFFER_SIZE];
  uint32_t size;
} interest_params_t;

typedef struct ndn_interest {
  uint32_t nonce;                /**< nonce of the interest */
  uint64_t lifetime;             /**< lifetime of the interest */

  uint8_t can_be_prefix;         /**< if present, the name element in the interest is a prefix, exact, or full name of the requested data packet */
  uint8_t can_be_prefix_enabled; /**< indicates if \ref can_be_prefix field is set */

  uint8_t must_be_fresh;         /**< indicates whether a content store may satisfy the interest with stale data */
  uint8_t must_be_fresh_enabled; /**< indicates if \ref must_be_fresh field is set */

  interest_params_t parameters;  /**< parameters of the interest */
  uint8_t parameters_enabled;    /**< indicates if parameters field is set */

  uint8_t hop_limit;             /**< hop limit */
} ndn_interest_t;


static inline void interest_create(ndn_interest_t *interest)
{
    /** initialize all fields of the interest with '0' */
    memset(interest, 0, sizeof(ndn_interest_t));
    /** set default network lifetime */
    interest->lifetime = INTEREST_DEFAULT_LIFETIME;
};

/**
 * @brief       Encodes an Interest message
 *
 * @param[out]  out      output buffer
 * @param[in]   intmsg   Interset to encode into @p out
 * @retval      0 on succes
 * @retval      -1 output buffer @p out was NULL
 * @retval      -2 interest @p intmsg was NULL
 */
int8_t interest_encode(ndnup_buffer_write_t *out, interest_t *intmsg);

#ifdef __cplusplus
}
#endif

#endif /* INTEREST_H */

/**
 * @}
 */
