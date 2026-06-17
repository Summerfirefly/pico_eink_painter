add_library(epaper_driver
    EPD_4in0e.c
)

target_include_directories(epaper_driver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
