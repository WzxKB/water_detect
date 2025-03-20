set(SOURCES 
"main.cc"
    "matrix_keyboard/matrix_keyboard.cc"
    "board_lcd/board_lcd.c"
    "board_adc/board_adc.cc"
    "application.cc"
    "ui.cc")
file(GLOB UI_SOURCES 
    "ui/custom/*.c"
    "ui/generated/*.c"
    "ui/generated/guider_customer_fonts/*.c"
    "ui/generated/guider_fonts/*.c"
    "ui/generated/images/*.c"
    
)

list(APPEND SOURCES ${UI_SOURCES})

set(INCLUDE_DIRS
    "ui/custom"
    "ui/generated"
    "ui/generated/guider_customer_fonts"
    "ui/generated/guider_fonts"
    "ui/generated/images"
    "board_lcd"
    "matrix_keyboard"
    "board_adc"
    "."
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDE_DIRS}
    WHOLE_ARCHIVE
)
add_definitions(-DLV_LVGL_H_INCLUDE_SIMPLE)
