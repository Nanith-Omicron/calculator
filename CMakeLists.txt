cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(pico_sdk_import.cmake)
project(calculator C CXX ASM)
pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR} inc/*.h)
link_directories(${CMAKE_SOURCE_DIR} lib/*.h)
 

add_compile_definitions(TFT_ENABLE_GREEN=1)   
add_compile_definitions(TFT_ENABLE_ALL=1)   
add_compile_definitions(TFT_ENABLE_TEXT=1)
 
add_compile_definitions(TFT_ENABLE_SHAPES=1)
add_compile_definitions(TFT_ENABLE_RESET=1)
add_compile_definitions(TFT_ENABLE_ROTATE=1)

add_executable(${PROJECT_NAME} 
    main.c 
    src/display.c 
    src/sysUtils.c 
)

add_subdirectory(lib-st7735)

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib 
    hardware_spi 
    hardware_dma
    hardware_irq
    st7735
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})