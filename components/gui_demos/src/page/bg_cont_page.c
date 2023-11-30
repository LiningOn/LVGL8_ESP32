#include "bg_cont_page.h"

lv_obj_t *bg_cont_obj;

void bg_cont_page(uint32_t delay)
{
    lv_obj_t *scr = lv_scr_act();

    /* create bg cont */
    bg_cont_obj = lv_obj_create(scr);
    lv_obj_remove_style_all(bg_cont_obj);
    lv_obj_set_size(bg_cont_obj, 172, 320);
    lv_obj_set_style_radius(bg_cont_obj, 15, 0);
    lv_obj_set_style_bg_opa(bg_cont_obj, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(bg_cont_obj, lv_color_black(), 0);
    lv_obj_center(bg_cont_obj);

    obj_set_anim(bg_cont_obj, -320, 0, 500, delay, anim_set_y_cb, NULL, lv_anim_path_bounce);
}
