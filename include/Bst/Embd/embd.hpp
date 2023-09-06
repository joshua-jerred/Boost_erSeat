/**
 * @file embd.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded base header
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

// clang-format off

#ifndef BOOSTERSEAT_EMBEDDED
#warning "BOOSTERSEAT_EMBEDDED not defined."
#endif /* BOOSTERSEAT_EMBEDDED */

#ifndef BST_EMBD_CONFIG_HPP_
#define BST_EMBD_CONFIG_HPP_

#ifdef BST_EMBD_STM32F4xx
  #define EMBD_DEVICE_SET
  #define BST_EMBD_STM32
  #define STM32_HAL_INCLUDE "stm32f4xx_hal.h"
  #ifndef ARM_NONE_EABI
    #error "ARM_NONE_EABI not defined."
  #endif
#endif

#ifdef BST_EMBD_SIM
  #define EMBD_DEVICE_SET
#endif

#ifndef EMBD_DEVICE_SET
  #error "No device set."
#endif

// clang-format on

#endif /* BST_EMBD_CONFIG_HPP_ */
