/*
 * Copyright (C) 2019 Safety IO
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        helper.h
 * @brief       Helper functions for NDNup
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include <stdint.h>

#include "ndnv03/buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline size_t get_var_size(uint32_t var)
{
    if (var < 253) {
        return 1;
    }

    if (var <= 0xFFFF) {
        return 3;
    }

    return 5;
}

static inline size_t get_block_size(uint32_t type, uint32_t payload_size)
{
    return payload_size + get_var_size(type) + get_var_size(payload_size);
}

#ifdef __cplusplus
}
#endif

#endif /* HELPER_H */

/**
 * @}
 */
