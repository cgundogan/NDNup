/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        data.h
 * @brief       Data structures and functions for NDN data messages
 * @author      Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright   MIT License
 * @addtogroup  Decoder
 * @{
 */

#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <string.h>

#include "tlv.h"
#include "name.h"
#include "helper.h"
#include "constants.h"
#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Representation of a Data message
 */
typedef struct {
  ndn_name_t name;               /**< name of the interest */

} ndn_data_t;


static inline void data_create(ndn_data_t *data)
{
    /** initialize all fields of the data with '0' */
    memset(data, 0, sizeof(ndn_data_t));
};

static size_t get_interest_size(const ndn_data_t* data)
{
    size_t size = get_name_block_size(&(data->name));

    return size;
};

/**
 * @brief       Encodes an Data message
 *
 * @param[out]  out      output buffer
 * @param[in]   intmsg   Data to encode into @p out
 * @retval      0 on succes
 * @retval      -1 output buffer @p out was NULL
 * @retval      -2 @p data was NULL
 */
int8_t data_encode(buffer_write_t *out, ndn_data_t *data);

#ifdef __cplusplus
}
#endif

#endif /* DATA_H */

/**
 * @}
 */
