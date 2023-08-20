/**
 * @file gpio.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded GPIO Interface
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

#ifndef BST_EMBD_GPIO_HPP_
#define BST_EMBD_GPIO_HPP_

#include "embd.hpp"
#include "pins.hpp"

namespace bst {

class Gpio {
public:
  Gpio(GPIO_TypeDef *port, uint16_t pin) : port_(port), pin_number_(pin) {
  }
  ~Gpio() = default;

  void digitalWrite(bool output_high) {
    HAL_GPIO_WritePin(port_, pin_number_,
                      output_high ? GPIO_PIN_SET : GPIO_PIN_RESET);
  }
  void toggle() {
    HAL_GPIO_TogglePin(port_, pin_number_);
  }

private:
  GPIO_TypeDef *port_ = nullptr;
  uint16_t pin_number_ = 0;
};

} // namespace bst

#endif /* BSTE_GPIO_HPP_ */