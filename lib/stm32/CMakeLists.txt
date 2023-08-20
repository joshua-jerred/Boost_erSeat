message("Adding STM32 libraries")

add_subdirectory(CMSIS)
add_subdirectory(STM32F4xx_HAL_Driver)
add_subdirectory(Middlewares/ST/STM32_USB_Device_Library)