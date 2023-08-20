/**
 * @file gpio.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded Assert Library
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

#ifndef BST_EMBD_ASSERT_HPP_
#define BST_EMBD_ASSERT_HPP_

#include "embd.hpp"

namespace bst {}

#ifdef BST_EMBD_SIM

#include <cassert>
#define BST_ASSERT(x) assert(x)
#endif /* BST_EMBD_SIM */

#ifdef BST_EMBD_STM32F411

#endif /* BST_EMBD_STM32F411 */

#endif /* BST_EMBD_ASSERT_HPP_ */