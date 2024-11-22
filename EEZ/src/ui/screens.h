#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *tires;
    lv_obj_t *inverters;
    lv_obj_t *extra;
    lv_obj_t *lv_bat_voltage_s1;
    lv_obj_t *hv_soc_est_s1;
    lv_obj_t *sx_status_bar_s1;
    lv_obj_t *current_time;
    lv_obj_t *last_time;
    lv_obj_t *target_time;
    lv_obj_t *dx_status_bar_s1;
    lv_obj_t *sx_map_s1;
    lv_obj_t *lc_ctrl_s1;
    lv_obj_t *tc_ctrl_s1;
    lv_obj_t *tv_ctrl_s1;
    lv_obj_t *dx_map_s1;
    lv_obj_t *lv_bat_voltage_s2;
    lv_obj_t *hv_soc_est_s2;
    lv_obj_t *sx_status_bar_1;
    lv_obj_t *front_left_temp;
    lv_obj_t *obj0;
    lv_obj_t *front_left_bar;
    lv_obj_t *obj1;
    lv_obj_t *front_right_temp;
    lv_obj_t *obj2;
    lv_obj_t *front_right_bar;
    lv_obj_t *obj3;
    lv_obj_t *rear_left_temp;
    lv_obj_t *obj4;
    lv_obj_t *rear_left_bar;
    lv_obj_t *obj5;
    lv_obj_t *rear_right_temp;
    lv_obj_t *obj6;
    lv_obj_t *rear_right_bar;
    lv_obj_t *obj7;
    lv_obj_t *dx_status_bar_1;
    lv_obj_t *sx_map_s2;
    lv_obj_t *lc_ctrl_s2;
    lv_obj_t *tc_ctrl_s2;
    lv_obj_t *tv_ctrl_s2;
    lv_obj_t *dx_map_s2;
    lv_obj_t *lv_bat_voltage_s3;
    lv_obj_t *hv_soc_est_s3;
    lv_obj_t *sx_status_bar_s3;
    lv_obj_t *front_left_temp_inv;
    lv_obj_t *obj8;
    lv_obj_t *front_left_inv_state;
    lv_obj_t *front_right_temp_inv;
    lv_obj_t *obj9;
    lv_obj_t *front_right_inv_state;
    lv_obj_t *rear_left_temp_inv;
    lv_obj_t *obj10;
    lv_obj_t *rear_left_inv_state;
    lv_obj_t *rear_right_temp_inv;
    lv_obj_t *obj11;
    lv_obj_t *rear_right_inv_state;
    lv_obj_t *dx_status_bar_s3;
    lv_obj_t *sx_map_s3;
    lv_obj_t *lc_ctrl_s3;
    lv_obj_t *tc_ctrl_s3;
    lv_obj_t *tv_ctrl_s3;
    lv_obj_t *dx_map_s3;
    lv_obj_t *lv_bat_voltage_s4;
    lv_obj_t *hv_soc_est_s4;
    lv_obj_t *cooling_sys_bar;
    lv_obj_t *cooling_sys_temp;
    lv_obj_t *throttle_perc;
    lv_obj_t *rear_brake_bar;
    lv_obj_t *front_brake_bar;
    lv_obj_t *sx_map_s4;
    lv_obj_t *lc_ctrl_s4;
    lv_obj_t *tc_ctrl_s4;
    lv_obj_t *tv_ctrl_s4;
    lv_obj_t *dx_map_s4;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_TIRES = 2,
    SCREEN_ID_INVERTERS = 3,
    SCREEN_ID_EXTRA = 4,
};

void create_screen_main();
void tick_screen_main();

void create_screen_tires();
void tick_screen_tires();

void create_screen_inverters();
void tick_screen_inverters();

void create_screen_extra();
void tick_screen_extra();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/