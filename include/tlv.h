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

#ifndef NDN_UP_TLV_H
#define NDN_UP_TLV_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A enum which holds the TLV-TYPE number assignments. See also
 *  https://named-data.net/doc/NDN-packet-spec/current/types.html
 */
typedef enum tlv_type {
	interest                           = 0x05,
	data                               = 0x06,
	name                               = 0x07,
	generic_Name_Component	           = 0x08,
	implicit_sha256_digest_component   = 0x01,
	parameters_sha256_digest_component = 0x02,
	can_be_prefix	                   = 0x21,
	must_be_fresh	                   = 0x12,
	forwarding_hint	                   = 0x1e,
	nonce	                           = 0x0a,
	interest_lifetime	               = 0x0c,
	hop_limit	                       = 0x22,
	parameters	                       = 0x24,
	meta_info	                       = 0x14,
	content	                           = 0x15,
	signature_info	                   = 0x16,
	signature_value	                   = 0x17,
	content_type	                   = 0x18,
	freshness_period	               = 0x19,
	final_block_id	                   = 0x1a,
	signature_type	                   = 0x1b,
	key_locator                        = 0x1c,
	key_digest                         = 0x1d,
	delegation                         = 0x1f,
	preference                         = 0x1e
} tlv_types_t;

#ifdef __cplusplus
}
#endif

#endif /* NDN_UP_TLV_H */

/**
 * @}
 */
