/*
 * Copyright (C) 2019 Safety IO 
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file        constants.h
 * @brief       Constants for NDNup 
 * @author      Michael Frey <michael.frey@safetyio.com>
 * @copyright   MIT License
 * @addtogroup  NDNup Minimal Standalone NDN Packet Parser
 * @{
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 
 */
#ifndef NDN_NAME_COMPONENTS_SIZE 
#define NDN_NAME_COMPONENTS_SIZE            (10u)
#endif 

/**
 * 
 */
#ifndef NDN_INTEREST_PARAMETERS_BUFFER_SIZE
#define NDN_INTEREST_PARAMETERS_BUFFER_SIZE (248u)
#endif 
        
/**
 * 
 */
#ifndef NDN_NAME_COMPONENT_BUFFER_SIZE
#define NDN_NAME_COMPONENT_BUFFER_SIZE      (36u)
#endif 

/**
 * 
 */
#ifndef NDN_NAME_COMPONENT_BLOCK_SIZE
#define NDN_NAME_COMPONENT_BLOCK_SIZE       (38u)
#endif 

#ifdef __cplusplus
}
#endif

#endif /* CONSTANTS_H */

/**
 * @}
 */
