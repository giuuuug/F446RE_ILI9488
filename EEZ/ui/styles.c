#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "screens.h"

//
// Style: arc_map_style
//

void init_style_arc_map_style_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_width(style, 5);
    lv_style_set_arc_rounded(style, true);
    lv_style_set_arc_color(style, lv_color_hex(0xffd01d1d));
};

lv_style_t *get_style_arc_map_style_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_arc_map_style_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_arc_map_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_rounded(style, true);
    lv_style_set_arc_width(style, 4);
    lv_style_set_pad_top(style, 6);
    lv_style_set_pad_bottom(style, 6);
    lv_style_set_pad_left(style, 6);
    lv_style_set_pad_right(style, 6);
};

lv_style_t *get_style_arc_map_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_arc_map_style_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_arc_map_style_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 100);
    lv_style_set_bg_color(style, lv_color_hex(0xffd01d1d));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_arc_map_style_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_arc_map_style_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_arc_map_style(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_arc_map_style_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_arc_map_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_arc_map_style_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_arc_map_style(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_arc_map_style_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_arc_map_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_arc_map_style_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_arc_map_style,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_arc_map_style,
    };
    remove_style_funcs[styleIndex](obj);
}

