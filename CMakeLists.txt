# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(PICO_BOARD pico2 CACHE STRING "Board type")
set(PICO_SDK_PATH ${USERHOME}/.pico-sdk/sdk)
set(picotool_DIR ${PICO_SDK_PATH}/../picotool)
set(pioasm_DIR ${PICO_SDK_PATH}/../pioasm)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(eink_photo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

set(TARGET_DEVICE waveshare_4in0e_driver)
#set(TARGET_DEVICE waveshare_rp2350_photo_painter)

add_subdirectory(lib/${TARGET_DEVICE})
add_subdirectory(lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src)

aux_source_directory(src eink_photo_src)

add_executable(eink_photo
    main.c
    ${eink_photo_src}
)

pico_set_program_name(eink_photo "eink_photo")
pico_set_program_version(eink_photo "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(eink_photo 0)
pico_enable_stdio_usb(eink_photo 1)

# Add the standard library to the build
target_link_libraries(eink_photo
    pico_rand
    pico_stdlib
    ${TARGET_DEVICE}
    no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

# Add the standard include files to the build
target_include_directories(eink_photo PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

pico_add_extra_outputs(eink_photo)
