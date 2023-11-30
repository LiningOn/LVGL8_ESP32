#include "ui_memory_check_page.h"

static lv_mem_monitor_t mon;
static uint32_t used_kb;
static uint32_t used_kb_tenth;
static uint32_t pre_rate, rate;
static uint32_t total_size;

static lv_obj_t *return_btn;
static lv_style_t icon_style;
static lv_obj_t *ui_memory_used_cont;
static lv_obj_t *ui_memory_used_rate_arc;
static lv_obj_t *ui_memory_used_rate_label;
static lv_obj_t *ui_memory_label_cont;
static lv_obj_t *line;
static lv_obj_t *ui_memory_kb_label;
static lv_obj_t *ui_used_memory_label;
static lv_timer_t *timer;

static const char *TAG = "cpu used rate";

static void set_angle(void *obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void ui_memory_arc_anim(uint32_t delay)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, ui_memory_used_rate_arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 0);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_values(&a, 0, rate);
    lv_anim_start(&a);
}

static void ui_memory_check_page_anim_in(uint32_t delay)
{
    obj_set_anim(return_btn, -320, 0, 500, delay, anim_set_y_cb, NULL, lv_anim_path_bounce);
    obj_set_anim(ui_memory_used_cont, -172, 0, 500, delay, anim_set_x_cb, NULL, lv_anim_path_bounce);
    obj_set_anim(ui_memory_label_cont, 172, 0, 500, delay, anim_set_x_cb, NULL, lv_anim_path_bounce);
    ui_memory_arc_anim(500);
}

static void ui_memory_check_page_anim_out(uint32_t delay)
{
    obj_set_anim(return_btn, 0, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(ui_memory_used_cont, 0, -172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(ui_memory_label_cont, 0, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
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
            lv_timer_del(timer);
            ui_memory_check_page_anim_out(0);
            main_menu_page(0);
            break;
        default:
            break;
    }
}

/* timer cb */
static void timer_cb(lv_timer_t *timer)
{
    uint32_t used_size = total_size - mon.free_size;
    used_kb = used_size / 1024;
    used_kb_tenth = (used_size - (used_kb * 1024)) / 102;
    rate = mon.used_pct;

    if(pre_rate != rate)
    {
        ui_memory_arc_anim(0);
    }
    lv_obj_align_to(ui_memory_used_rate_label, ui_memory_used_rate_arc, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text_fmt(ui_memory_used_rate_label, "%d%%", rate);
    pre_rate = rate;
    
    lv_obj_align_to(ui_used_memory_label, line, LV_ALIGN_OUT_TOP_MID, 0, 0);
    lv_label_set_text_fmt(ui_used_memory_label, "%d.%d", used_kb, used_kb_tenth);
}

void ui_memory_check_page(uint32_t delay)
{
    lv_group_t *group = get_group();

    LV_FONT_DECLARE(my_font_chinese_18);

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

    /* ui memory cont */
    ui_memory_used_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(ui_memory_used_cont);
    lv_obj_set_size(ui_memory_used_cont, 172, 180);
    lv_obj_set_style_radius(ui_memory_used_cont, 20, 0);
    lv_obj_set_style_bg_opa(ui_memory_used_cont, LV_OPA_0, 0);
    lv_obj_align_to(ui_memory_used_cont, bg_cont_obj, LV_ALIGN_TOP_MID, 0, 30);

    /* ui memory title label */
    lv_obj_t *ui_memory_title_label = lv_label_create(ui_memory_used_cont);
    lv_label_set_text_fmt(ui_memory_title_label, "UI 内存");
    lv_obj_set_style_text_font(ui_memory_title_label, &my_font_chinese_18, 0);
    lv_obj_set_style_text_color(ui_memory_title_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(ui_memory_title_label, LV_OPA_COVER, 0);
    lv_obj_align_to(ui_memory_title_label, ui_memory_used_cont, LV_ALIGN_TOP_MID, 0, 5);

    /* ui memory arc */
    ui_memory_used_rate_arc = lv_arc_create(ui_memory_used_cont);
    lv_obj_set_size(ui_memory_used_rate_arc, 130, 130);
    lv_obj_set_style_arc_width(ui_memory_used_rate_arc, 10, 0);
    lv_obj_set_style_arc_width(ui_memory_used_rate_arc, 10, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(ui_memory_used_rate_arc, lv_color_hex(MY_COLOR_SPRING_GREEN), LV_PART_INDICATOR);
    lv_obj_set_style_arc_opa(ui_memory_used_rate_arc, LV_OPA_10, 0);
    lv_arc_set_rotation(ui_memory_used_rate_arc, 270);
    lv_arc_set_bg_angles(ui_memory_used_rate_arc, 0, 360);
    lv_obj_remove_style(ui_memory_used_rate_arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(ui_memory_used_rate_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align_to(ui_memory_used_rate_arc, ui_memory_used_cont, LV_ALIGN_TOP_MID, 0, 50);

    /* ui memory used rate label */
    ui_memory_used_rate_label = lv_label_create(ui_memory_used_cont);
    lv_label_set_text_fmt(ui_memory_used_rate_label, "%d%%", rate);
    lv_obj_set_style_text_font(ui_memory_used_rate_label, &lv_font_montserrat_30, 0);
    lv_obj_set_style_text_color(ui_memory_used_rate_label, lv_color_hex(MY_COLOR_SPRING_GREEN), 0);
    lv_obj_set_style_text_opa(ui_memory_used_rate_label, LV_OPA_COVER, 0);
    lv_obj_align_to(ui_memory_used_rate_label, ui_memory_used_rate_arc, LV_ALIGN_CENTER, 0, 0);

    /* ui memory label cont */
    ui_memory_label_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(ui_memory_label_cont);
    lv_obj_set_size(ui_memory_label_cont, 172, 100);
    lv_obj_set_style_radius(ui_memory_label_cont, 20, 0);
    lv_obj_set_style_bg_opa(ui_memory_label_cont, LV_OPA_0, 0);
    lv_obj_align_to(ui_memory_label_cont, ui_memory_used_cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    /* line */
    static lv_point_t line_points[] = { {0, 5}, {85, 5} };

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 3);
    lv_style_set_line_color(&style_line, lv_color_hex(MY_COLOR_SPRING_GREEN));
    lv_style_set_line_opa(&style_line, LV_OPA_COVER);
    lv_style_set_line_rounded(&style_line, true);

    line = lv_line_create(ui_memory_label_cont);
    lv_line_set_points(line, line_points, 2);
    lv_obj_add_style(line, &style_line, 0);
    lv_obj_align_to(line, ui_memory_label_cont, LV_ALIGN_LEFT_MID, 25, 0);

    /* ui used memory label */
    ui_used_memory_label = lv_label_create(ui_memory_label_cont);
    lv_label_set_text_fmt(ui_used_memory_label, "%d.%d", 0, 0);
    lv_obj_set_style_text_font(ui_used_memory_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(ui_used_memory_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(ui_used_memory_label, LV_OPA_COVER, 0);
    lv_obj_align_to(ui_used_memory_label, line, LV_ALIGN_OUT_TOP_MID, 0, 0);

    lv_mem_monitor(&mon);
    total_size = mon.total_size;

    /* ui memory total label */
    lv_obj_t *ui_memory_total_label = lv_label_create(ui_memory_label_cont);
    lv_label_set_text_fmt(ui_memory_total_label, "%d", total_size / 1024);
    lv_obj_set_style_text_font(ui_memory_total_label, &lv_font_montserrat_30, 0);
    lv_obj_set_style_text_color(ui_memory_total_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(ui_memory_total_label, LV_OPA_COVER, 0);
    lv_obj_align_to(ui_memory_total_label, line, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    /* ui memory KB label */
    ui_memory_kb_label = lv_label_create(ui_memory_label_cont);
    lv_label_set_text_fmt(ui_memory_kb_label, "KB");
    lv_obj_set_style_text_font(ui_memory_kb_label, &my_font_chinese_18, 0);
    lv_obj_set_style_text_color(ui_memory_kb_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(ui_memory_kb_label, LV_OPA_COVER, 0);
    lv_obj_align_to(ui_memory_kb_label, line, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /* timer create */
    timer = lv_timer_create(timer_cb, 800, NULL);

    lv_group_add_obj(group, return_btn);

    ui_memory_check_page_anim_in(delay);
}