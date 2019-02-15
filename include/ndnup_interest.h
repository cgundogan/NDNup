/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        ndnup_interest.h
 * @brief       Interest add functions to handle Interest messages
 * @author      Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright   MIT License
 * @addtogroup  NDNup
 * @{
 */

#ifndef NDNUP_INTEREST_H
#define NDNUP_INTEREST_H

#include <stdio.h>
#include <stdint.h>

#include "ndnup_buffer.h"

/**
 * @brief An Interest message
 */
typedef struct {
    uint8_t test;
} ndnup_interest_t;

/**
 * @brief       Encodes an Interest message
 *
 * @param[out]  out      output buffer
 * @param[in]   intmsg   Interset to encode into @p out
 * @retval      0 on succes
 * @retval      -1 on failure
 */
int8_t ndnup_interest_encode(ndnup_buffer_write_t *out, ndnup_interest_t *intmsg);

#endif /* NDNUP_INTEREST_H */

/**
 * @}
 */
