#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: arc_map_style
lv_style_t *get_style_arc_map_style_INDICATOR_DEFAULT();
lv_style_t *get_style_arc_map_style_MAIN_DEFAULT();
lv_style_t *get_style_arc_map_style_KNOB_DEFAULT();
void add_style_arc_map_style(lv_obj_t *obj);
void remove_style_arc_map_style(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/