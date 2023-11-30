idf_component_register(
    SRCS 
        "main.c"
        
    INCLUDE_DIRS 
        "."
    
    REQUIRES 
        lvgl
        lv_fs_if
        lvgl_disp_port
        lvgl_indev_port
        fastscan
        gui_demos)
