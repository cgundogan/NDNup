/*
 * Copyright (C) 2019 Safety IO
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        tlv.h
 * @brief       TLV-TYPE number assignments
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef NDNUP_TLV_H
#define NDNUP_TLV_H

#ifndef NDN_TLV_MAJOR_VERSION
#define NDN_TLV_MAJOR_VERSION 0
#endif

#ifndef NDN_TLV_MINOR_VERSION
#define NDN_TLV_MINOR_VERSION 3
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A enum which holds the TLV-TYPE number assignments. See also
 *  https://named-data.net/doc/NDN-packet-spec/current/types.html
 */
typedef enum tlv_type {
        tlv_interest                           = 0x05,
        tlv_data                               = 0x06,
        tlv_name                               = 0x07,
        tlv_generic_name_component             = 0x08,
        tlv_implicit_sha256_digest_component   = 0x01,
        tlv_parameters_sha256_digest_component = 0x02,
        tlv_can_be_prefix                      = 0x21,
        tlv_must_be_fresh                      = 0x12,
        tlv_forwarding_hint                    = 0x1e,
        tlv_nonce                              = 0x0a,
        tlv_interest_lifetime                  = 0x0c,
        tlv_hop_limit                          = 0x22,
        tlv_parameters                         = 0x24,
        tlv_meta_info                          = 0x14,
        tlv_content                            = 0x15,
        tlv_signature_info                     = 0x16,
        tlv_signature_value                    = 0x17,
        tlv_content_type                       = 0x18,
        tlv_freshness_period                   = 0x19,
        tlv_final_block_id                     = 0x1a,
        tlv_signature_type                     = 0x1b,
        tlv_key_locator                        = 0x1c,
        tlv_key_digest                         = 0x1d,
        tlv_delegation                         = 0x1f,
        tlv_preference                         = 0x1e
} tlv_types_t;

#ifdef __cplusplus
}
#endif

#endif /* NDNUP_TLV_H */

/**
 * @}
 */
