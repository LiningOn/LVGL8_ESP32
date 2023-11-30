set(component_srcs 
    "my_font_chinese_18.c"
)

idf_component_register(
    SRCS 
        "${component_srcs}"

    INCLUDE_DIRS 
        "."

    REQUIRES
        "lvgl"
)