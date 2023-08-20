/**
 * @file gpio.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded UART Driver (For STM32F4xx only at the moment)
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

#include <Bst/Embd/uart.hpp>

namespace bst {

Uart::Uart(UART_HandleTypeDef *uart_handle, DMA_HandleTypeDef *rx_dma,
           DMA_HandleTypeDef *tx_dma)
    : uart_handle_(uart_handle), rx_dma_(rx_dma), tx_dma_(tx_dma) {
}

void Uart::init() {
  HAL_UART_Init(uart_handle_);
  HAL_UART_Receive_DMA(uart_handle_, rx_buffer_.data(), kUartRxBufferSize);
}

void Uart::send(const etl::span<const uint8_t> &data) {
  HAL_UART_Transmit(uart_handle_, data.data(), data.size(), kUartTimeout);
}

etl::array<uint8_t, kUartRxBufferSize> &Uart::receive() {
  return rx_buffer_;
}

} // namespace bst