/**
 * @file pins.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded GPIO Pins
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

// #ifndef PINS_HPP_
// #define PINS_HPP_

// #include "embd.hpp"
// #include <cstdint>

// namespace bst {

// // #ifdef BST_EMBD_SIM
// // enum class Pin { SimPin1, SimPin2, SimPin3 };
// // enum class PinMode {
// //   Input,
// //   Output,
// // };
// // struct PinExtraArgs {
// //   PinExtraArgs() = default;
// // };
// // #endif /* BST_EMBD_SIM */

// #ifdef BST_EMBD_STM32F4xx

// enum class Pin : uint16_t { PB0, PB7, PB14, PC13 };
// enum class PinMode {
//   Input,
//   OutputPushPull,
//   OutputOpenDrain,
//   AlternateFunctionPushPull,
//   AlternateFunctionOpenDrain
// };

// struct PinExtraArgs {
//   enum class Pull { None, Up, Down };
//   enum class Speed { Low, Medium, High, VeryHigh };
//   enum class DefaultState { Low, High };

//   const Pull pull = Pull::None;
//   const Speed speed = Speed::Low;
//   const DefaultState default_state = DefaultState::Low;
// };

// #endif /* BST_EMBD_STM32F411 */

// } // namespace bst

// #endif /* PINS_HPP_ */