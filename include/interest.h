/*
 * Copyright (C) 2019 Safety IO
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        interest.h
 * @brief       Data structures and functions for NDN Interest messages
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef INTEREST_H
#define INTEREST_H

#include <stdint.h>
#include <string.h>

#include "tlv.h"
#include "name.h"
#include "helper.h"
#include "constants.h"
#include "buffer.h"

/**
 * The default lifetime of an Interest packet in milliseconds.
 */
#ifndef INTEREST_DEFAULT_LIFETIME
#define INTEREST_DEFAULT_LIFETIME (4000u)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief NDN Interest parameters element
 * {@
 */
typedef struct interest_params {
  uint8_t value[NDN_INTEREST_PARAMETERS_BUFFER_SIZE]; /**< actual interest parameters */
  uint32_t size;                                      /**< overall size of the interest parameters */
} interest_params_t;
/** @} */

/**
 * @brief NDN Interest message
 * @{
 */
typedef struct ndn_interest {
    ndn_name_t name;               /**< name of the interest */

    uint32_t nonce;                /**< nonce of the interest */
    uint32_t lifetime;             /**< lifetime of the interest */

    uint8_t can_be_prefix;         /**< if present, the name element in the interest is a prefix, exact, or full name of the requested data packet */

    uint8_t must_be_fresh;         /**< indicates whether a content store may satisfy the interest with stale data */

    interest_params_t parameters;  /**< parameters of the interest */

    uint8_t hop_limit;             /**< hop limit */

    uint8_t lifetime_enabled :1;      /**< indicates if the lifetime field is set*/
    uint8_t can_be_prefix_enabled :1; /**< indicates if @ref can_be_prefix field is set */
    uint8_t must_be_fresh_enabled :1; /**< indicates if @ref must_be_fresh field is set */
    uint8_t parameters_enabled :1;    /**< indicates if parameters field is set */
    uint8_t hop_limit_enabled :1;     /**< indicates if field @ref hop_limit is set */
} ndn_interest_t;
/** @} */


static inline void interest_create(ndn_interest_t *interest)
{
    /** initialize all fields of the interest with '0' */
    memset(interest, 0, sizeof(ndn_interest_t));
}

/**
 * @brief       Returns the length of an encoded Interest message in bytes
 *
 * @param[in]   interest   Interest messages
 * @return      Length of the encoded message in bytes
 */
size_t interest_get_size(const ndn_interest_t* interest);

/**
 * @brief       Encodes an Interest message
 *
 * @param[out]  out      output buffer
 * @param[in]   interest   Interset to encode into @p out
 * @retval      0 on succes
 * @retval      -1 output buffer @p out was NULL
 * @retval      -2 @p interest was NULL
 */
int8_t interest_encode(buffer_write_t *out, ndn_interest_t *interest);


/**
 * @brief       Decodes an Interest message
 *
 * @param[out]  interest Interest to decode from @p in 
 * @param[in]   in       input buffer
 * @retval      0 on succes
 * @retval      -1 interest @p interest  was NULL
 * @retval      -2 input buffer @p in was NULL
 * @retval      -3 data in @p in to decode was not an Interest packet 
 */
int8_t interest_decode(ndn_interest_t *interest, buffer_read_t *in);


#ifdef __cplusplus
}
#endif

#endif /* INTEREST_H */

/**
 * @}
 */
