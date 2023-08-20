/**
 * @file gpio.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief The STM32 GPIO Implementation
 * @date 2023-08-10
 * @copyright Copyright (c) 2023
 */

#ifdef BST_EMBD_STM32F4xx

#include "stm32f4xx_hal.h"
#include <Bst/Embd/gpio.hpp>

namespace bst {

Gpio::Gpio(Pin pin, PinMode mode, PinExtraArgs extra_args)
    : pin_(pin), mode_(mode), extra_args_(extra_args) {
  switch (pin) {
  case Pin::PC13:
    pin_number_ = GPIO_PIN_13;
    port_ = GPIOC;
    break;
  default:
    // assert(false);
    break;
  };
}

Gpio::~Gpio() = default;

void Gpio::digitalWrite(bool output_high) {
  HAL_GPIO_WritePin(port_, pin_number_,
                    output_high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Gpio::toggle() {
  HAL_GPIO_TogglePin(port_, pin_number_);
}

}; // namespace bst

#endif