add_library(STM32_USB_DEVICE_LIBRARY INTERFACE)
target_include_directories(STM32_USB_DEVICE_LIBRARY INTERFACE
  Core/Inc
  Class/CDC/Inc
)
target_sources(STM32_USB_DEVICE_LIBRARY INTERFACE
  Core/Src/usbd_core.c
  Core/Src/usbd_ctlreq.c
  Core/Src/usbd_ioreq.c
  Class/CDC/Src/usbd_cdc.c
)
target_link_libraries(STM32_USB_DEVICE_LIBRARY INTERFACE ${STM32_COMPILE_DEFS})