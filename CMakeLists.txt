# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(${USERHOME}/.pico-sdk/sdk/${sdkVersion}/external/pico_sdk_import.cmake)

project(eink_photo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(lib/epaper_driver)
add_subdirectory(lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src)

aux_source_directory(dev_config dev_config_src)
aux_source_directory(src eink_photo_src)

# Add executable. Default name is the project name, version 0.1

add_executable(eink_photo
    main.c
    ${eink_photo_src}
    ${dev_config_src}
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
    epaper_driver
    no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

# Add the standard include files to the build
target_include_directories(eink_photo PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

pico_add_extra_outputs(eink_photo)
