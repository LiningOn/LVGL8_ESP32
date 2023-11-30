set(component_srcs 
    "src/app/app.c"
    "src/anim/anim.c"

    "src/img/img.c"
    "src/img/astronaut1.c"
    "src/img/astronaut2.c"
    "src/img/astronaut3.c"
    "src/img/astronaut4.c"
    "src/img/astronaut5.c"
    "src/img/astronaut6.c"
    "src/img/astronaut7.c"
    "src/img/astronaut8.c"
    "src/img/astronaut9.c"
    "src/img/astronaut10.c"
    "src/img/astronaut11.c"
    "src/img/astronaut12.c"
    "src/img/astronaut13.c"
    "src/img/astronaut14.c"

    "src/page/boot_page.c"
    "src/page/main_menu_page.c"
    "src/page/bg_cont_page.c"
    "src/page/wifi_page.c"
    "src/page/sdcard_info_page.c"
    "src/page/ui_memory_check_page.c"

    "src/font/my_font_chinese_18.c"
)

idf_component_register(
    SRCS 
        "${component_srcs}"

    INCLUDE_DIRS 
        "include/app"
        "include/anim"
        "include/page"
        "include/config"

    REQUIRES
        "lvgl"
        "lv_fs_if"
        "lvgl_indev_port"
        "sd_fat"
        "fastscan"
)