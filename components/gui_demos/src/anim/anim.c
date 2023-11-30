#include "anim.h"

void anim_set_x_cb(void *var, uint32_t v)
{
    lv_obj_set_x(var, v);
}

void anim_set_y_cb(void *var, uint32_t v)
{
    lv_obj_set_y(var, v);
}

void obj_set_anim(lv_obj_t *obj, int32_t start, int32_t end, uint32_t time, uint32_t delay, lv_anim_exec_xcb_t exec_cb, lv_anim_ready_cb_t ready_cb, lv_anim_path_cb_t path_cb)
{
    lv_anim_t a;

    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, start, end);
    lv_anim_set_time(&a, time);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)exec_cb);
    lv_anim_set_ready_cb(&a, ready_cb);
    lv_anim_set_path_cb(&a, path_cb);
    lv_anim_start(&a);
}
