/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        data.h
 * @brief       Data structures and functions for NDN Data messages
 * @author      Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright   MIT License
 * @addtogroup  Decoder
 * @{
 */

#ifndef NDNV03_DATA_H
#define NDNV03_DATA_H

#include <stdint.h>
#include <string.h>

#include "ndnv03/tlv.h"
#include "ndnv03/name.h"
#include "ndnv03/helper.h"
#include "ndnv03/constants.h"
#include "ndnv03/buffer.h"

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
 * @brief Representation of the MetaInfo TLV
 * @{
 */
typedef struct {
    tlfield_t contenttype;              /**< content type */
    tlfield_t freshnessperiod;          /**< period the data is marked as fresh */
    ndn_component_t finalblockid;       /**< indicating the final name component */
} ndn_data_metainfo_t;
/** @} */

/**
 * @brief Representation of the Content TLV
 * @{
 */
typedef struct {
    uint8_t value[DATA_CONTENT_LENGTH];  /**< actual content */
    size_t length;                       /**< length of the content */
} ndn_data_content_t;
/** @} */

/**
 * @brief NDN Data message
 * @{
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
} ndnv03_data_t;
/** @} */

static inline void data_create(ndnv03_data_t *data)
{
    /** initialize all fields of the data with '0' */
    memset(data, 0, sizeof(ndnv03_data_t));
}

/**
 * @brief       Encodes an Data message
 *
 * @param[out]  out      output buffer
 * @param[in]   data     Data to encode into @p out
 * @retval      0 on succes
 * @retval      -1 output buffer @p out was NULL
 * @retval      -2 @p data was NULL
 */
int8_t data_encode(buffer_write_t *out, ndnv03_data_t *data);

/**
 * @brief       Decodes a Data message
 *
 * @param[out]  data     Data to decode from @p in
 * @param[in]   in       input buffer
 * @retval      0 on succes
 * @retval      -1 data @p data  was NULL
 * @retval      -2 input buffer @p in was NULL
 * @retval      -3 data in @p in to decode was not a Data packet
 */
int8_t data_decode(ndnv03_data_t *data, buffer_read_t *in);

#ifdef __cplusplus
}
#endif

#endif /* NDNV03_DATA_H */

/**
 * @}
 */
