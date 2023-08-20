add_library(STM32F4XX_HAL_DRIVER INTERFACE)
target_include_directories(STM32F4XX_HAL_DRIVER INTERFACE Inc)
target_sources(STM32F4XX_HAL_DRIVER INTERFACE
  # HAL
  Src/stm32f4xx_hal.c

  Src/stm32f4xx_hal_adc_ex.c
  Src/stm32f4xx_hal_adc.c
  Src/stm32f4xx_hal_cortex.c
  Src/stm32f4xx_hal_dac_ex.c
  Src/stm32f4xx_hal_dac.c
  Src/stm32f4xx_hal_dma_ex.c
  Src/stm32f4xx_hal_dma.c
  
  Src/stm32f4xx_hal_uart.c

  Src/stm32f4xx_hal_pcd.c
  Src/stm32f4xx_hal_pcd_ex.c
  Src/stm32f4xx_hal_rcc.c
  Src/stm32f4xx_hal_gpio.c

  # LL
  Src/stm32f4xx_ll_usb.c
)
target_link_libraries(STM32F4XX_HAL_DRIVER INTERFACE ${STM32_INCLUDE_LIB})