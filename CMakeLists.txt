cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(OBC-send)
add_library( obc INTERFACE)

pico_sdk_init()

target_sources(obc INTERFACE
${CMAKE_CURRENT_LIST_DIR}/flash.c
${CMAKE_CURRENT_LIST_DIR}/UART.c
${CMAKE_CURRENT_LIST_DIR}/IMU.c
${CMAKE_CURRENT_LIST_DIR}/main.c
)

target_link_libraries(obc INTERFACE
    pico_stdlib
    hardware_i2c
    hardware_uart
    hardware_spi
    hardware_irq
    hardware_dma
)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} obc)
target_compile_definitions(${PROJECT_NAME} PRIVATE obc)

pico_enable_stdio_usb(${PROJECT_NAME} 1) # from video
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})