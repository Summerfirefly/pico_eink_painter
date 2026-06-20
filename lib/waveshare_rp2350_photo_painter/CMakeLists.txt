aux_source_directory(. waveshare_rp2350_photo_painter_src)

add_library(waveshare_rp2350_photo_painter
    ${waveshare_rp2350_photo_painter_src}
)

target_link_libraries(waveshare_rp2350_photo_painter
    pico_stdlib
    hardware_adc
    hardware_i2c
    hardware_spi
    hardware_watchdog
)

target_include_directories(waveshare_rp2350_photo_painter PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
