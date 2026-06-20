aux_source_directory(. waveshare_4in0e_driver_src)

add_library(waveshare_4in0e_driver
    ${waveshare_4in0e_driver_src}
)

target_link_libraries(waveshare_4in0e_driver
    hardware_gpio
)

target_include_directories(waveshare_4in0e_driver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
