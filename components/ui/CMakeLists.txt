file(GLOB_RECURSE srcs *.c
                    custom/*.c
                    generated/*.c
                    generated/guider_customer_fonts/*.c
                    generated/guider_fonts/*.c
                    generated/images/*.c
                    )

set(include_dirs 
    . 
    custom 
    generated 
    generated/guider_customer_fonts
    generated/guider_fonts
    generated/images
    )
 
idf_component_register(
    SRC_DIRS .
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    PRIV_REQUIRES "lvgl" 
)
## The purpose of opening this macro is to change the path of "lvgl/ lvgl.h" to "lvgl.h".
target_compile_definitions(${COMPONENT_LIB} PRIVATE "LV_LVGL_H_INCLUDE_SIMPLE=1")