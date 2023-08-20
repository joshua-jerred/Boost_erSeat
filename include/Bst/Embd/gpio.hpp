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
  Gpio(Pin pin, PinMode mode, PinExtraArgs extra_args = PinExtraArgs());
  ~Gpio();

  void digitalWrite(bool output_high);
  void toggle();

  bool digitalRead();

private:
  Pin pin_;
  PinMode mode_;
  PinExtraArgs extra_args_;

  uint32_t pin_number_ = 0;
  GPIO_TypeDef *port_ = nullptr;
};

} // namespace bst

#endif /* BSTE_GPIO_HPP_ */