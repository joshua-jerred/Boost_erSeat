add_library(CMSIS INTERFACE)
target_include_directories(CMSIS INTERFACE 
  Include
  Device/ST/STM32F4xx/Include
  Core/Include
)