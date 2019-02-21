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
 * @brief Maximal length of content in Data messages
 */
#ifndef DATA_CONTENT_LENGTH
#define DATA_CONTENT_LENGTH (16)
#endif

/**
 * Representation of the MetaInfo TLV
 */
typedef struct {
    tlfield_t contenttype;              /**< content type */
    tlfield_t freshnessperiod;          /**< period the data is marked as fresh */
    ndn_component_t finalblockid;       /**< indicating the final name component */
} ndn_data_metainfo_t;

/**
 * Representation of the Content TLV
 */
typedef struct {
    uint8_t value[DATA_CONTENT_LENGTH];  /**< actual content */
    size_t length;                       /**< length of the content */
} ndn_data_content_t;

/**
 * Representation of a Data message
 */
typedef struct {
    ndn_name_t name;                       /**< name of the data */
    ndn_data_metainfo_t metainfo;          /**< MetaInfo TLV */
    ndn_data_content_t content;            /**< Content TLV */
    uint8_t metainfo_enabled :1;           /**< indicates if @ref metainfo is included */
    uint8_t contenttype_enabled :1;        /**< indicates if @ref metainfo::contenttype is set */
    uint8_t freshnessperiod_enabled :1;    /**< indicates if @ref metainfo::freshnessperiod is set */
    uint8_t finalblockid_enabled :1;       /**< indicates if @ref metainfo::finalblockid is set */
    uint8_t content_enabled :1;            /**< indicates if @ref content is set */
} ndn_data_t;

static inline void data_create(ndn_data_t *data)
{
    /** initialize all fields of the data with '0' */
    memset(data, 0, sizeof(ndn_data_t));
}

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
