#include "main_menu_page.h"
#include "config.h"

static lv_obj_t *wifi_menu_btn_obj;
static lv_obj_t *sdcard_menu_btn_obj;
static lv_obj_t *ui_memory_menu_btn_obj;
static lv_obj_t *astronaut_cont;

LV_IMG_DECLARE(astronaut1);
LV_IMG_DECLARE(astronaut2);
LV_IMG_DECLARE(astronaut3);
LV_IMG_DECLARE(astronaut4);
LV_IMG_DECLARE(astronaut5);
LV_IMG_DECLARE(astronaut6);
LV_IMG_DECLARE(astronaut7);
LV_IMG_DECLARE(astronaut8);
LV_IMG_DECLARE(astronaut9);
LV_IMG_DECLARE(astronaut10);
LV_IMG_DECLARE(astronaut11);
LV_IMG_DECLARE(astronaut12);
LV_IMG_DECLARE(astronaut13);
LV_IMG_DECLARE(astronaut14);

const lv_img_dsc_t *astronaut_imgs[14] = {
    &astronaut1, 
    &astronaut2,
    &astronaut3, 
    &astronaut4,
    &astronaut5, 
    &astronaut6,
    &astronaut7, 
    &astronaut8,
    &astronaut9, 
    &astronaut10,
    &astronaut11, 
    &astronaut12,
    &astronaut13, 
    &astronaut14,
};

void main_menu_page_anim_in(uint32_t delay)
{
    obj_set_anim(wifi_menu_btn_obj, -80, 5, 1000, delay + 500, anim_set_x_cb, NULL, lv_anim_path_bounce);
    obj_set_anim(sdcard_menu_btn_obj, 80, -5, 1000, delay + 500, anim_set_x_cb, NULL, lv_anim_path_bounce);
    obj_set_anim(ui_memory_menu_btn_obj, -167, 5, 1000, delay + 500, anim_set_x_cb, NULL, lv_anim_path_overshoot);
    obj_set_anim(astronaut_cont, 167, 0, 1000, delay + 500, anim_set_x_cb, NULL, lv_anim_path_overshoot);
}

void main_menu_page_anim_out(uint32_t delay)
{
    obj_set_anim(wifi_menu_btn_obj, 5, -80, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(sdcard_menu_btn_obj, 5, 80, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(ui_memory_menu_btn_obj, 5, -167, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(astronaut_cont, 0, 167, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
}

static void remove_group_obj(void)
{
    lv_group_remove_obj(wifi_menu_btn_obj);
    lv_group_remove_obj(sdcard_menu_btn_obj);
    lv_group_remove_obj(ui_memory_menu_btn_obj);
}

static void wifi_menu_btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
        case LV_EVENT_CLICKED:
            remove_group_obj();
            main_menu_page_anim_out(0);
            wifi_page(500);
            break;
        default:
            break;
    }
}

static void sdcard_menu_btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
        case LV_EVENT_CLICKED:
            remove_group_obj();
            main_menu_page_anim_out(0);
            sdcard_info_page(500);
            break;
        default:
            break;
    }
}

static void ui_memory_menu_btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
        case LV_EVENT_CLICKED:
            remove_group_obj();
            main_menu_page_anim_out(0);
            ui_memory_check_page(500);
            break;
        default:
            break;
    }
}

static void astronaut_anim(void)
{
    lv_obj_t *a = lv_animimg_create(astronaut_cont);
    lv_obj_center(a);
    lv_animimg_set_src(a, astronaut_imgs, 14);   
    lv_animimg_set_duration(a, 1000);                   
    lv_animimg_set_repeat_count(a, LV_ANIM_REPEAT_INFINITE);   
    lv_animimg_start(a);        
}

void main_menu_page(uint32_t delay)
{
    lv_group_t *group = get_group();

    LV_FONT_DECLARE(my_font_chinese_18);
    
    /* create wifi menu btn */
    wifi_menu_btn_obj = lv_btn_create(bg_cont_obj);

    lv_obj_remove_style_all(wifi_menu_btn_obj);
    lv_obj_set_size(wifi_menu_btn_obj, 75, 75);
    lv_obj_set_style_radius(wifi_menu_btn_obj, 10, 0);
    lv_obj_set_style_bg_color(wifi_menu_btn_obj, lv_color_hex(MY_COLOR_DODGER_BLUE), 0);
    lv_obj_set_style_bg_opa(wifi_menu_btn_obj, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(wifi_menu_btn_obj, lv_color_hex(MY_COLOR_DODGER_BLUE), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(wifi_menu_btn_obj, LV_OPA_80, LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(wifi_menu_btn_obj, LV_OPA_60, LV_STATE_PRESSED);
    lv_obj_align(wifi_menu_btn_obj, LV_ALIGN_BOTTOM_LEFT, 5, -5);

    lv_obj_t *wifi_menu_icon_label = lv_label_create(wifi_menu_btn_obj);
    lv_label_set_text(wifi_menu_icon_label, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(wifi_menu_icon_label, &lv_font_montserrat_30, 0);
    lv_obj_set_style_text_color(wifi_menu_icon_label, lv_color_white(), 0);
    lv_obj_center(wifi_menu_icon_label);

    lv_obj_add_event_cb(wifi_menu_btn_obj, wifi_menu_btn_event_cb, LV_EVENT_CLICKED, NULL);

    /* create sdcard menu btn */
    sdcard_menu_btn_obj = lv_btn_create(bg_cont_obj);

    lv_obj_remove_style_all(sdcard_menu_btn_obj);
    lv_obj_set_size(sdcard_menu_btn_obj, 75, 75);
    lv_obj_set_style_radius(sdcard_menu_btn_obj, 10, 0);
    lv_obj_set_style_bg_color(sdcard_menu_btn_obj, lv_color_hex(MY_COLOR_DODGER_BLUE), 0);
    lv_obj_set_style_bg_opa(sdcard_menu_btn_obj, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(sdcard_menu_btn_obj, lv_color_hex(MY_COLOR_DODGER_BLUE), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(sdcard_menu_btn_obj, LV_OPA_80, LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(sdcard_menu_btn_obj, LV_OPA_60, LV_STATE_PRESSED);
    lv_obj_align(sdcard_menu_btn_obj, LV_ALIGN_BOTTOM_RIGHT, -5, -5);

    lv_obj_t *sdcard_menu_icon_label = lv_label_create(sdcard_menu_btn_obj);
    lv_label_set_text(sdcard_menu_icon_label, LV_SYMBOL_SD_CARD);
    lv_obj_set_style_text_font(sdcard_menu_icon_label, &lv_font_montserrat_30, 0);
    lv_obj_set_style_text_color(sdcard_menu_icon_label, lv_color_white(), 0);
    lv_obj_center(sdcard_menu_icon_label);

    lv_obj_add_event_cb(sdcard_menu_btn_obj, sdcard_menu_btn_event_cb, LV_EVENT_CLICKED, NULL);

    /* create terminal menu cont */
    ui_memory_menu_btn_obj = lv_btn_create(bg_cont_obj);

    lv_obj_remove_style_all(ui_memory_menu_btn_obj);
    lv_obj_set_size(ui_memory_menu_btn_obj, 162, 60);
    lv_obj_set_style_radius(ui_memory_menu_btn_obj, 10, 0);
    lv_obj_set_style_bg_color(ui_memory_menu_btn_obj, lv_color_hex(MY_COLOR_SPRING_GREEN), 0);
    lv_obj_set_style_bg_opa(ui_memory_menu_btn_obj, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(ui_memory_menu_btn_obj, lv_color_hex(MY_COLOR_SPRING_GREEN), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_memory_menu_btn_obj, LV_OPA_80, LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_memory_menu_btn_obj, LV_OPA_60, LV_STATE_PRESSED);
    lv_obj_align_to(ui_memory_menu_btn_obj, wifi_menu_btn_obj, LV_ALIGN_OUT_TOP_LEFT, 0, -10);

    lv_obj_t *terminal_text_label = lv_label_create(ui_memory_menu_btn_obj);
    lv_label_set_text(terminal_text_label, "UI 内存监测");
    lv_obj_set_style_text_font(terminal_text_label, &my_font_chinese_18, 0);
    lv_obj_set_style_text_opa(terminal_text_label, LV_OPA_COVER, 0);
    lv_obj_set_style_text_color(terminal_text_label, lv_color_white(), 0);
    lv_obj_center(terminal_text_label);

    lv_obj_add_event_cb(ui_memory_menu_btn_obj, ui_memory_menu_btn_event_cb, LV_EVENT_CLICKED, NULL);

    /* astronaut cont */
    astronaut_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(astronaut_cont);
    lv_obj_set_size(astronaut_cont, 150, 150);
    lv_obj_set_style_radius(astronaut_cont, 75, 0);
    lv_obj_set_style_bg_color(astronaut_cont, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(astronaut_cont, LV_OPA_0, 0);
    lv_obj_align(astronaut_cont, LV_ALIGN_TOP_MID, 0, 10);

    /* 添加组 */
    lv_group_add_obj(group, ui_memory_menu_btn_obj);
    lv_group_add_obj(group, wifi_menu_btn_obj);
    lv_group_add_obj(group, sdcard_menu_btn_obj);
    
    /* 页面入场动画 */
    astronaut_anim();
    main_menu_page_anim_in(delay);
}
