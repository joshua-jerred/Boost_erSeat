/**
 * @file gpio.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded UART Driver (For STM32F4xx only at the moment)
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

#ifndef BST_EMBD_UART_HPP_
#define BST_EMBD_UART_HPP_

#include "embd.hpp"
#include <etl/array.h>
#include <etl/span.h>

// extern "C" {
#include <stm32f4xx_hal.h>
// }

namespace bst {

constexpr uint32_t kUartTimeout = 1000;

template <uint16_t RxBufferSize = 512>
class Uart {
public:
  Uart(UART_HandleTypeDef *uart_handle, DMA_HandleTypeDef *rx_dma,
       DMA_HandleTypeDef *tx_dma)
      : uart_handle_(uart_handle), rx_dma_(rx_dma), tx_dma_(tx_dma) {
  }
  void init() {
    HAL_UART_Init(uart_handle_);
    HAL_UART_Receive_DMA(uart_handle_, rx_buffer_.data(), RxBufferSize);
  }
  void send(const etl::span<const uint8_t> &data) {
    HAL_UART_Transmit(uart_handle_, data.data(), data.size(), kUartTimeout);
  }
  etl::array<uint8_t, RxBufferSize> &receive() {
    return rx_buffer_;
  }

  uint32_t getNumBytesReceived() const {
    return RxBufferSize - __HAL_DMA_GET_COUNTER(rx_dma_);
  }

  uint32_t isBufferFull() const {
    return __HAL_DMA_GET_COUNTER(rx_dma_) == 0;
  }

  bool isBusy() const {
    return HAL_UART_GetState(uart_handle_) != HAL_UART_STATE_READY;
  }

  bool isIdle() const {
    return HAL_UART_GetState(uart_handle_) == HAL_UART_STATE_READY;
  }

  bool isReceiving() const {
    return HAL_UART_GetState(uart_handle_) == HAL_UART_STATE_BUSY_RX;
  }

  void clearBuffer() {
    HAL_UART_AbortReceive(uart_handle_);
    HAL_UART_Receive_DMA(uart_handle_, rx_buffer_.data(), RxBufferSize);
  }

private:
  UART_HandleTypeDef *uart_handle_;
  DMA_HandleTypeDef *rx_dma_;
  DMA_HandleTypeDef *tx_dma_;

  etl::array<uint8_t, RxBufferSize> rx_buffer_{};
};

} // namespace bst

#endif /* BST_EMBD_UART_HPP_ */