#include "boot_page.h"

static void anim_ready_cb(lv_anim_t *a)
{
    obj_set_anim(a->var, 110, 320, 500, 2000, anim_set_y_cb, lv_obj_del_anim_ready_cb, lv_anim_path_ease_in);
}

void boot_page_run(void)
{
    LV_IMG_DECLARE(img);

    lv_obj_t *scr = lv_scr_act();
    lv_obj_clean(scr);

    lv_obj_remove_style_all(scr);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    lv_obj_t *image = lv_img_create(scr);
    lv_img_set_src(image, &img);
    lv_obj_align(image, LV_ALIGN_TOP_MID, 0, -100);

    obj_set_anim(image, -100, 110, 800, 1000, anim_set_y_cb, anim_ready_cb, lv_anim_path_bounce);
}