#include "wifi_page.h"

static lv_obj_t *return_btn;
static lv_obj_t *wifi_switch_btn;
static lv_obj_t *wifi_connect_cont;
static lv_obj_t *wifi_connected_cont;
static lv_obj_t *wifi_disconnected_cont;
static lv_obj_t *wifi_state_label;
static lv_style_t icon_style;
static lv_style_t wifi_switch_btn_default_style;
static lv_style_t wifi_switch_btn_focused_style;
static wifi_state_t wifi_switch_state = WIFI_STATE_CLOSED;
static lv_obj_t *wifi_ip_addr_label;
static lv_obj_t *wifi_ssid_label;
static lv_timer_t *timer;
static bool wifi_connected_page_show = true;

LV_FONT_DECLARE(my_font_chinese_18);

static void wifi_connected_page(void);
static void wifi_disconnected_page(void);

static void wifi_page_anim_in(uint32_t delay)
{
    obj_set_anim(return_btn, -320, 0, 500, delay, anim_set_y_cb, NULL, lv_anim_path_bounce);
    obj_set_anim(wifi_switch_btn, -172, 0, 500, delay, anim_set_x_cb, NULL, lv_anim_path_overshoot);
    obj_set_anim(wifi_connect_cont, -172, 0, 500, delay + 300, anim_set_x_cb, NULL, lv_anim_path_overshoot);
}

static void wifi_page_anim_out(uint32_t delay)
{
    obj_set_anim(wifi_connect_cont, 0, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(wifi_switch_btn, 0, -172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
    obj_set_anim(return_btn, 0, 172, 500, delay, anim_set_x_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
}

static void wifi_connected_anim_out(void)
{
    obj_set_anim(wifi_connected_cont, 10, -70, 500, 3000, anim_set_y_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
}

static void wifi_connected_anim_in(void)
{
    obj_set_anim(wifi_connected_cont, -70, 10, 500, 0, anim_set_y_cb, wifi_connected_anim_out, lv_anim_path_bounce);
}

static void wifi_disconnected_anim_out(void)
{
    obj_set_anim(wifi_disconnected_cont, 10, -70, 500, 3000, anim_set_y_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_out);
}

static void wifi_disconnected_anim_in(void)
{
    obj_set_anim(wifi_disconnected_cont, -70, 10, 500, 0, anim_set_y_cb, wifi_disconnected_anim_out, lv_anim_path_bounce);
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
            lv_group_remove_obj(wifi_switch_btn);
            lv_timer_del(timer);
            wifi_page_anim_out(0);
            main_menu_page(0);
            break;
        default:
            break;
    }
}

static void wifi_switch_btn_cb(lv_event_cb_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    switch(code)
    {
        case LV_EVENT_FOCUSED:
            lv_style_set_bg_opa(&wifi_switch_btn_focused_style, LV_OPA_80);
            lv_obj_add_style(obj, &wifi_switch_btn_focused_style, LV_STATE_FOCUSED);
            break;
        case LV_EVENT_CLICKED:
            if(wifi_switch_state == WIFI_STATE_CLOSED)
            {
                wifi_start();
                lv_label_set_text(wifi_state_label, "已开启");
                lv_obj_set_style_text_color(wifi_state_label, lv_color_white(), 0);
                lv_obj_set_style_text_opa(wifi_state_label, LV_OPA_COVER, 0);
                lv_style_set_bg_color(&wifi_switch_btn_default_style, lv_color_hex(MY_COLOR_SPRING_GREEN));
                lv_obj_add_style(obj, &wifi_switch_btn_default_style, LV_STATE_DEFAULT);
                wifi_switch_state = WIFI_STATE_OPENED;
            }
            else if(wifi_switch_state == WIFI_STATE_OPENED)
            {
                wifi_stop();
                lv_label_set_text(wifi_state_label, "已关闭");
                lv_obj_set_style_text_color(wifi_state_label, lv_color_white(), 0);
                lv_obj_set_style_text_opa(wifi_state_label, LV_OPA_60, 0);
                lv_style_set_bg_color(&wifi_switch_btn_default_style, lv_color_hex(MY_COLOR_DODGER_BLUE));
                lv_obj_add_style(obj, &wifi_switch_btn_default_style, LV_STATE_DEFAULT);
                wifi_switch_state = WIFI_STATE_CLOSED;
            }
            break;
        default:
            break;
    }
}

/* timer cb */
static void timer_cb(lv_timer_t *timer)
{
    if(wifi_ip_got_state)
    {
        if(wifi_connected_page_show)
        {
            wifi_connected_page();
            wifi_connected_anim_in();
            wifi_connected_page_show = false;
        }
        lv_label_set_text(wifi_state_label, "已连接");
        lv_label_set_text_fmt(wifi_ssid_label, "%s", WIFI_SSID);
        lv_label_set_text_fmt(wifi_ip_addr_label, "%d.%d.%d.%d", wifi_ip_addr[0], wifi_ip_addr[1], wifi_ip_addr[2], wifi_ip_addr[3]);
    }
    else
    {
        if(wifi_switch_state == WIFI_STATE_OPENED)
        {
            if(wifi_connected_page_show == false)
            {
                wifi_disconnected_page();
                wifi_disconnected_anim_in();
                wifi_connected_page_show = true;
            }
            lv_label_set_text(wifi_state_label, "未连接");
        }
        else
        {
            if(wifi_connected_page_show == false)
            {
                wifi_disconnected_page();
                wifi_disconnected_anim_in();
                wifi_connected_page_show = true;
            }
            lv_label_set_text(wifi_state_label, "已关闭");
        }
        
        lv_label_set_text_fmt(wifi_ssid_label, " ");
        lv_label_set_text_fmt(wifi_ip_addr_label, " ");
    }
}

static void wifi_connected_page(void)
{
    /* wifi connected cont */
    wifi_connected_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(wifi_connected_cont);
    lv_obj_set_size(wifi_connected_cont, 162, 60); 
    lv_obj_set_style_radius(wifi_connected_cont, 20, 0);
    lv_obj_set_style_bg_opa(wifi_connected_cont, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(wifi_connected_cont, lv_color_white(), 0);
    lv_obj_align_to(wifi_connected_cont, bg_cont_obj, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *label = lv_label_create(wifi_connected_cont);
    lv_label_set_text(label, "连接成功");
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_set_style_text_opa(label, LV_OPA_COVER, 0);
    lv_obj_set_style_text_font(label, &my_font_chinese_18, 0);
    lv_obj_align_to(label, wifi_connected_cont, LV_ALIGN_CENTER, 0, 0);
}

static void wifi_disconnected_page(void)
{
    /* wifi connected cont */
    wifi_disconnected_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(wifi_disconnected_cont);
    lv_obj_set_size(wifi_disconnected_cont, 162, 60); 
    lv_obj_set_style_radius(wifi_disconnected_cont, 20, 0);
    lv_obj_set_style_bg_opa(wifi_disconnected_cont, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(wifi_disconnected_cont, lv_color_white(), 0);
    lv_obj_align_to(wifi_disconnected_cont, bg_cont_obj, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *label = lv_label_create(wifi_disconnected_cont);
    lv_label_set_text(label, "连接断开");
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_set_style_text_opa(label, LV_OPA_COVER, 0);
    lv_obj_set_style_text_font(label, &my_font_chinese_18, 0);
    lv_obj_align_to(label, wifi_disconnected_cont, LV_ALIGN_CENTER, 0, 0);
}

void wifi_page(uint32_t delay)
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

    /* wifi switch */
    lv_style_init(&wifi_switch_btn_default_style);
    lv_style_set_radius(&wifi_switch_btn_default_style, 10);
    lv_style_set_bg_color(&wifi_switch_btn_default_style, lv_color_hex(MY_COLOR_DODGER_BLUE));
    lv_style_set_bg_opa(&wifi_switch_btn_default_style, LV_OPA_COVER);

    lv_style_init(&wifi_switch_btn_focused_style);
    lv_style_set_bg_opa(&wifi_switch_btn_focused_style, LV_OPA_80);

    wifi_switch_btn = lv_btn_create(bg_cont_obj);
    lv_obj_remove_style_all(wifi_switch_btn);
    lv_obj_set_size(wifi_switch_btn, 172, 80);
    lv_obj_add_style(wifi_switch_btn, &wifi_switch_btn_default_style, 0);
    lv_obj_add_style(wifi_switch_btn, &wifi_switch_btn_focused_style, LV_STATE_FOCUSED);
    lv_obj_align_to(wifi_switch_btn, bg_cont_obj, LV_ALIGN_TOP_LEFT, 0, 30);

    lv_obj_t *wifi_open_label = lv_label_create(wifi_switch_btn);
    lv_label_set_text(wifi_open_label, "开启WIFI");
    lv_obj_set_style_text_color(wifi_open_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(wifi_open_label, LV_OPA_COVER, 0);
    lv_obj_set_style_text_font(wifi_open_label, &my_font_chinese_18, 0);
    lv_obj_align_to(wifi_open_label, wifi_switch_btn, LV_ALIGN_TOP_LEFT, 10, 5);

    wifi_state_label = lv_label_create(wifi_switch_btn);
    lv_label_set_text(wifi_state_label, "已关闭");
    lv_obj_set_style_text_color(wifi_state_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(wifi_state_label, LV_OPA_60, 0);
    lv_obj_set_style_text_font(wifi_state_label, &my_font_chinese_18, 0);
    lv_obj_align_to(wifi_state_label, wifi_switch_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -5);

    lv_obj_add_event_cb(wifi_switch_btn, wifi_switch_btn_cb, LV_EVENT_CLICKED, wifi_state_label);

    if(wifi_switch_state == WIFI_STATE_CLOSED)
    {
        if(!wifi_ip_got_state)
        {
            lv_label_set_text(wifi_state_label, "未连接");
        }
        else
        {
            lv_label_set_text(wifi_state_label, "已关闭");
        }
        
        lv_obj_set_style_text_color(wifi_state_label, lv_color_white(), 0);
        lv_obj_set_style_text_opa(wifi_state_label, LV_OPA_60, 0);
        lv_style_set_bg_color(&wifi_switch_btn_default_style, lv_color_hex(MY_COLOR_DODGER_BLUE));
        lv_obj_add_style(wifi_switch_btn, &wifi_switch_btn_default_style, LV_STATE_DEFAULT);
    }
    else
    {
        if(wifi_ip_got_state)
        {
            lv_label_set_text(wifi_state_label, "已连接");
        }
        else
        {
            lv_label_set_text(wifi_state_label, "已开启");
        }

        lv_obj_set_style_text_opa(wifi_state_label, LV_OPA_COVER, 0);
        lv_obj_set_style_text_color(wifi_state_label, lv_color_white(), 0);  
        lv_style_set_bg_color(&wifi_switch_btn_default_style, lv_color_hex(MY_COLOR_SPRING_GREEN));
        lv_obj_add_style(wifi_switch_btn, &wifi_switch_btn_default_style, LV_STATE_DEFAULT);
    }

    /* wifi cont */
    wifi_connect_cont = lv_obj_create(bg_cont_obj);
    lv_obj_remove_style_all(wifi_connect_cont);
    lv_obj_set_size(wifi_connect_cont, 172, 190); 
    lv_obj_set_style_radius(wifi_connect_cont, 10, 0);
    lv_obj_set_style_bg_opa(wifi_connect_cont, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(wifi_connect_cont, lv_color_hex(MY_COLOR_DODGER_BLUE), 0);
    lv_obj_align_to(wifi_connect_cont, wifi_switch_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    /* WLAN */
    lv_obj_t *wifi_wlan_label = lv_label_create(wifi_connect_cont);
    lv_label_set_text(wifi_wlan_label, "WLAN");
    lv_obj_set_style_text_color(wifi_wlan_label, lv_color_white(), 0);
    lv_obj_set_style_text_opa(wifi_wlan_label, LV_OPA_COVER, 0);
    lv_obj_set_style_text_font(wifi_wlan_label, &my_font_chinese_18, 0);
    lv_obj_align_to(wifi_wlan_label, wifi_connect_cont, LV_ALIGN_TOP_MID, 0, 5);

    /* ssid cont*/
    lv_obj_t *ssid_cont = lv_obj_create(wifi_connect_cont);
    lv_obj_remove_style_all(ssid_cont);
    lv_obj_set_size(ssid_cont, 162, 50);
    lv_obj_set_style_radius(ssid_cont, 10, 0);
    lv_obj_set_style_bg_color(ssid_cont, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(ssid_cont, LV_OPA_40, 0);
    lv_obj_align_to(ssid_cont, wifi_connect_cont, LV_ALIGN_TOP_LEFT, 5, 40);

    /* ssid icon */
    lv_obj_t *wifi_icon_label = lv_label_create(ssid_cont);
    lv_label_set_text(wifi_icon_label, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(wifi_icon_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_opa(wifi_icon_label, LV_OPA_80, 0);
    lv_obj_set_style_text_color(wifi_icon_label, lv_color_white(), 0);
    lv_obj_align_to(wifi_icon_label, ssid_cont, LV_ALIGN_LEFT_MID, 10, 0);

    /* ssid label*/
    wifi_ssid_label = lv_label_create(ssid_cont);
    lv_label_set_long_mode(wifi_ssid_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(wifi_ssid_label, 110);
    lv_obj_set_style_text_font(wifi_ssid_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_opa(wifi_ssid_label, LV_OPA_80, 0);
    lv_obj_set_style_text_color(wifi_ssid_label, lv_color_white(), 0);
    lv_obj_align_to(wifi_ssid_label, wifi_icon_label, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /* ip cont*/
    lv_obj_t *ip_cont = lv_obj_create(wifi_connect_cont);
    lv_obj_remove_style_all(ip_cont);
    lv_obj_set_size(ip_cont, 162, 80);
    lv_obj_set_style_radius(ip_cont, 10, 0);
    lv_obj_set_style_bg_color(ip_cont, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(ip_cont, LV_OPA_40, 0);
    lv_obj_align_to(ip_cont, ssid_cont, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    /* ip icon*/
    lv_obj_t *wifi_ip_label = lv_label_create(ip_cont);
    lv_label_set_text_fmt(wifi_ip_label, "IP");
    lv_obj_set_style_text_font(wifi_ip_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_opa(wifi_ip_label, LV_OPA_80, 0);
    lv_obj_set_style_text_color(wifi_ip_label, lv_color_white(), 0);
    lv_obj_align_to(wifi_ip_label, ip_cont, LV_ALIGN_TOP_LEFT, 10, 10);

    /* ip label */
    wifi_ip_addr_label = lv_label_create(ip_cont);
    lv_obj_set_style_text_font(wifi_ip_addr_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_opa(wifi_ip_addr_label, LV_OPA_80, 0);
    lv_obj_set_style_text_color(wifi_ip_addr_label, lv_color_white(), 0);
    lv_obj_align_to(wifi_ip_addr_label, wifi_ip_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    /* timer create */
    timer = lv_timer_create(timer_cb, 500, NULL);

    /* 添加组 */
    lv_group_add_obj(group, return_btn);
    lv_group_add_obj(group, wifi_switch_btn);

    wifi_page_anim_in(delay);
}