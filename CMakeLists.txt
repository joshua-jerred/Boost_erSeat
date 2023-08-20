cmake_minimum_required(VERSION 3.14)
project(BoosterSeat VERSION 1.0)

# ------------------- Environmental Variables -------------------
option(BOOSTERSEAT_EMBEDDED "" OFF)
option(ARM_NONE_EABI "" OFF)
option(BST_EMBD_STM32_USB "" OFF)
option(BST_EMBD_STM32F411 "" OFF)
# ------------------- Environmental Variables -------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-unused-parameter")

set(COMMON_SOURCES

)
set(HOST_SOURCES
  src/stopwatch.cpp
  src/string_format.cpp
  src/time.cpp
  src/filesystem.cpp
  src/random.cpp
  src/timer.cpp
  src/rolling_average.cpp
  src/numbers.cpp
  #src/geo/geo_point.cpp
  #src/geo/geo_strings.cpp
)
set(EMBEDDED_SOURCES
  src/embedded/stm32/gpio.cpp
)


add_library(BoosterSeat INTERFACE)
target_include_directories(BoosterSeat INTERFACE include)

if(${BOOSTERSEAT_EMBEDDED})
  target_sources(BoosterSeat INTERFACE ${COMMON} ${EMBEDDED_SOURCES})
else()
  target_sources(BoosterSeat INTERFACE ${COMMON} ${HOST_SOURCES})
endif()


# ------------------- Embedded -------------------
if(${BOOSTERSEAT_EMBEDDED})
  message("BoosterSeat is being built for an embedded target")
  target_compile_definitions(BoosterSeat INTERFACE BOOSTERSEAT_EMBEDDED)

  set(STM32_ENABLED FALSE)
  set(STM32_INCLUDE_LIB "") # for use inside of other libraries (like STM32_USB_DEVICE_LIBRARY)
  set(STM32_COMPILE_DEFS "") # for use inside of other libraries (like STM32_USB_DEVICE_LIBRARY)

  if(${ARM_NONE_EABI})
    message("BoosterSeat is being built for an ARM target")
    target_compile_definitions(BoosterSeat INTERFACE ARM_NONE_EABI)
  endif()

  if(${BST_EMBD_STM32F411})
    message("BoosterSeat is being built for the STM32F411")
    set(STM32_ENABLED TRUE)
    set(STM32_INCLUDE_LIB STM32F4XX_HAL_DRIVER CMSIS)
    set(STM32_COMPILE_DEFS "-DSTM32F411xE -DBST_EMBD_STM32F4xx")
  endif()

  if(${STM32_ENABLED})
    if(${BST_EMBD_STM32_USB}) 
      set(STM32_INCLUDE_LIB ${STM32_INCLUDE_LIB} STM32_USB_DEVICE_LIBRARY)
    endif()

    message("BoosterSeat STM32 libraries: ${STM32_INCLUDE_LIB}")
    message("BoosterSeat STM32 compile definitions: ${STM32_COMPILE_DEFS}")
    target_compile_definitions(BoosterSeat INTERFACE 
      "${STM32_COMPILE_DEFS}"
    )
    target_link_libraries(BoosterSeat INTERFACE 
      ${STM32_INCLUDE_LIB}
    )

    add_subdirectory(lib/stm32)
  endif()

endif()

# ------------------- Host Tests -------------------
if(NOT ${ARM_NONE_EABI})
  add_subdirectory(tests)
endif()