#include "sdcard_info_page.h"

static lv_obj_t *return_btn;
static lv_style_t icon_style;
static lv_obj_t *sdcard_arc_cont;
static lv_obj_t *sdcard_memory_info_cont;
static lv_obj_t *sdcard_arc;
static lv_obj_t *sdcard_title_cont;
static lv_obj_t *sdcard_memory_used_rate_label;
static uint32_t sdcard_capacity_used_rate;

static void set_angle(void *obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void arc_anim(void)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, sdcard_arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 500);
    lv_anim_set_delay(&a, 1000);
    lv_anim_set_values(&a, 0, sdcard_capacity_used_rate);
    lv_anim_start(&a);
}

static void sdcard_info_page_anim_in(uint32_t delay)
{
    obj_set_anim(return_btn, -320, 0, 500, delay, anim_set_y_cb, NULL, lv_anim_path_overshoot);
    obj_set_anim(sdcard_arc_cont, -167, 0, 500, delay, anim_set_x_cb, NULL, lv_anim_path_overshoot);
    obj_set_anim(sdcard_memory_info_cont, -167, 6, 500, delay + 200, anim_set_x_cb, NULL, lv_anim_path_overshoot);
    obj_set_anim(sdcard_title_cont, -167, 6, 500, delay + 200, anim_set_x_cb, NULL, lv_anim_path_overshoot);
    arc_anim();
}

static void sdcard_info_page_anim_out(uint32_t delay)
{
    obj_set_anim(return_btn, 0, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(sdcard_arc_cont, 0, -167, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(sdcard_memory_info_cont, 6, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(sdcard_title_cont, 6, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
}

static void return_btn_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *label = lv_event_get_user_data(e);

    switch(code)
    {
        case LV_EVENT_FOCUSED:
            lv_style_set_text_opa(&icon_style, LV_OPA_COVER);
            lv_obj_add_style(label, &icon_style, LV_STATE_FOCUSED);
            break;
        case LV_EVENT_DEFOCUSED:
            lv_style_set_text_opa(&icon_style, LV_OPA_30);
            lv_obj_add_style(label, &icon_style, LV_EVENT_DEFOCUSED);
            break;
        case LV_EVENT_CLICKED:
            lv_group_remove_obj(return_btn);
            sdcard_info_page_anim_out(0);
            main_menu_page(0);
            break;
        default:
            break;
    }
}

static void arc_value_change_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *label = lv_event_get_user_data(e);

    switch(code)
    {
        case LV_EVENT_DRAW_PART_BEGIN:
            lv_obj_align_to(sdcard_memory_used_rate_label, sdcard_arc_cont, LV_ALIGN_CENTER, 0, -20);
            lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(obj));
            break;
        default:
            break;
    }
}

void sdcard_info_page(uint32_t delay)
{
    lv_group_t *group = get_group();

    /* retrun btn */
    return_btn = lv_btn_create(bg_cont_obj);
    lv_obj_remove_style_all(return_btn);
    lv_obj_set_size(return_btn, 30, 30);
    lv_obj_set_style_radius(return_btn, 15, 0);
    lv_obj_set_style_bg_color(return_btn, lv_color_white(), LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(return_btn, LV_OPA_30, LV_STATE_PRESSED);
    lv_obj_align(return_btn, LV_ALIGN_TOP_LEFT, 5, 10);

    lv_style_init(&icon_style);
    lv_style_set_text_color(&icon_style, lv_color_white());
    lv_style_set_text_opa(&icon_style, LV_OPA_50);
    lv_style_set_text_font(&icon_style, &lv_font_montserrat_20);

    lv_obj_t *return_icon_label = lv_label_create(return_btn);
    lv_label_set_text(return_icon_label, LV_SYMBOL_LEFT);
    lv_obj_add_style(return_icon_label, &icon_style, 0);
    lv_obj_add_event_cb(return_btn, return_btn_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(return_btn, return_btn_cb, LV_EVENT_FOCUSED, return_icon_label);
    lv_obj_add_event_cb(return_btn, return_btn_cb, LV_EVENT_DEFOCUSED, return_icon_label);
    lv_obj_align(return_icon_label, LV_ALIGN_CENTER, 0, 0);

    /* sdcard arc cont */
    sdcard_arc_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(sdcard_arc_cont);
    lv_obj_set_size(sdcard_arc_cont, 160, 160);
    lv_obj_set_style_bg_opa(sdcard_arc_cont, LV_OPA_0, 0);
    lv_obj_center(sdcard_arc_cont);

    /* sdcard title label */
    sdcard_title_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(sdcard_title_cont);
    lv_obj_set_size(sdcard_title_cont, 160, 20);
    lv_obj_set_style_bg_opa(sdcard_title_cont, LV_OPA_0, 0);
    lv_obj_align_to(sdcard_title_cont, sdcard_arc_cont, LV_ALIGN_OUT_TOP_MID, 0, -20);

    LV_FONT_DECLARE(my_font_chinese_18);

    lv_obj_t *sdcard_title_label = lv_label_create(sdcard_title_cont);
    lv_label_set_text(sdcard_title_label, "SD卡");
    lv_obj_set_style_text_font(sdcard_title_label, &my_font_chinese_18, 0);
    lv_obj_set_style_text_color(sdcard_title_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(sdcard_title_label, LV_OPA_COVER, 0);
    lv_obj_center(sdcard_title_label);

    /* sdcard memory used rate label */
    sdcard_memory_used_rate_label = lv_label_create(sdcard_arc_cont);
    lv_label_set_text_fmt(sdcard_memory_used_rate_label, "%d%%", 0);
    lv_obj_set_style_text_font(sdcard_memory_used_rate_label, &lv_font_montserrat_30, 0);
    lv_obj_set_style_text_color(sdcard_memory_used_rate_label, lv_color_hex(MY_COLOR_SPRING_GREEN), 0);
    lv_obj_set_style_text_opa(sdcard_memory_used_rate_label, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_memory_used_rate_label, sdcard_arc_cont, LV_ALIGN_CENTER, 0, -20);

    static lv_point_t line_points[] = { {0, 5}, {80, 5} };

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 3);
    lv_style_set_line_color(&style_line, lv_color_hex(MY_COLOR_SPRING_GREEN));
    lv_style_set_line_opa(&style_line, LV_OPA_COVER);
    lv_style_set_line_rounded(&style_line, true);

    lv_obj_t *line = lv_line_create(sdcard_arc_cont);
    lv_line_set_points(line, line_points, 2);
    lv_obj_add_style(line, &style_line, 0);
    lv_obj_center(line);

    lv_obj_t *sdcard_used_label = lv_label_create(sdcard_arc_cont);
    lv_label_set_text(sdcard_used_label, "已使用");
    lv_obj_set_style_text_font(sdcard_used_label, &my_font_chinese_18, 0);
    lv_obj_set_style_text_color(sdcard_used_label, lv_color_hex(MY_COLOR_SPRING_GREEN), 0);
    lv_obj_set_style_text_opa(sdcard_used_label, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_used_label, sdcard_arc_cont, LV_ALIGN_CENTER, 0, 20);

    /* sdcard arc */
    sdcard_arc = lv_arc_create(sdcard_arc_cont);
    lv_obj_set_size(sdcard_arc, 160, 160);
    lv_obj_set_style_arc_width(sdcard_arc, 15, 0);
    lv_obj_set_style_arc_width(sdcard_arc, 15, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(sdcard_arc, lv_color_hex(MY_COLOR_DARK_ORANGE), LV_PART_INDICATOR);
    lv_obj_set_style_arc_opa(sdcard_arc, LV_OPA_COVER, 0);
    lv_arc_set_rotation(sdcard_arc, 270);
    lv_arc_set_bg_angles(sdcard_arc, 0, 360);
    lv_obj_add_event_cb(sdcard_arc, arc_value_change_cb, LV_EVENT_DRAW_PART_BEGIN, sdcard_memory_used_rate_label);
    lv_obj_remove_style(sdcard_arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(sdcard_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_center(sdcard_arc);

    /* get sdcard capacity */
    uint32_t free_capacity, total_capacity, sdcard_capacity_used;
    
    get_sdcard_total_and_free_capacity(&free_capacity, &total_capacity);
    sdcard_capacity_used = total_capacity - free_capacity;
    sdcard_capacity_used_rate = (uint32_t)((float)sdcard_capacity_used / (float)total_capacity * 100);

    /* sdcard memory label */
    sdcard_memory_info_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(sdcard_memory_info_cont);
    lv_obj_set_size(sdcard_memory_info_cont, 160, 70);
    lv_obj_set_style_bg_opa(sdcard_memory_info_cont, LV_OPA_0, 0);
    lv_obj_align_to(sdcard_memory_info_cont, bg_cont_obj, LV_ALIGN_BOTTOM_MID, 0, -5);

    lv_obj_t *sdcard_total_label1 = lv_label_create(sdcard_memory_info_cont);
    lv_label_set_text_fmt(sdcard_total_label1, LV_SYMBOL_STOP);
    lv_obj_set_style_text_font(sdcard_total_label1, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(sdcard_total_label1, lv_color_hex(MY_COLOR_SPRING_GREEN), 0);
    lv_obj_set_style_text_opa(sdcard_total_label1, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_total_label1, sdcard_memory_info_cont, LV_ALIGN_TOP_LEFT, 0, 20);

    lv_obj_t *sdcard_total_label2 = lv_label_create(sdcard_memory_info_cont);
    lv_label_set_text_fmt(sdcard_total_label2, "Total");
    lv_obj_set_style_text_font(sdcard_total_label2, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(sdcard_total_label2, lv_color_white(), 0);
    lv_obj_set_style_text_opa(sdcard_total_label2, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_total_label2, sdcard_total_label1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t *sdcard_total_label3 = lv_label_create(sdcard_memory_info_cont);
    lv_label_set_text_fmt(sdcard_total_label3, "%dM", total_capacity);
    lv_obj_set_style_text_font(sdcard_total_label3, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(sdcard_total_label3, lv_color_white(), 0);
    lv_obj_set_style_text_opa(sdcard_total_label3, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_total_label3, sdcard_memory_info_cont, LV_ALIGN_TOP_RIGHT, 0, 17);

    lv_obj_t *sdcard_used_label1 = lv_label_create(sdcard_memory_info_cont);
    lv_label_set_text_fmt(sdcard_used_label1, LV_SYMBOL_STOP);
    lv_obj_set_style_text_font(sdcard_used_label1, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(sdcard_used_label1, lv_color_hex(MY_COLOR_DARK_ORANGE), 0);
    lv_obj_set_style_text_opa(sdcard_used_label1, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_used_label1, sdcard_memory_info_cont, LV_ALIGN_BOTTOM_LEFT, 0, -5);

    lv_obj_t *sdcard_used_label2 = lv_label_create(sdcard_memory_info_cont);
    lv_label_set_text_fmt(sdcard_used_label2, "Used");
    lv_obj_set_style_text_font(sdcard_used_label2, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(sdcard_used_label2, lv_color_white(), 0);
    lv_obj_set_style_text_opa(sdcard_used_label2, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_used_label2, sdcard_used_label1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t *sdcard_used_label3 = lv_label_create(sdcard_memory_info_cont);
    lv_label_set_text_fmt(sdcard_used_label3, "%dM", sdcard_capacity_used);
    lv_obj_set_style_text_font(sdcard_used_label3, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(sdcard_used_label3, lv_color_white(), 0);
    lv_obj_set_style_text_opa(sdcard_used_label3, LV_OPA_COVER, 0);
    lv_obj_align_to(sdcard_used_label3, sdcard_memory_info_cont, LV_ALIGN_BOTTOM_RIGHT, 0, -2);

    lv_group_add_obj(group, return_btn);

    sdcard_info_page_anim_in(delay);
}

