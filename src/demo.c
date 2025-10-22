#include <stdio.h>

#include "demo.h"

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#define LVGL_RESOURCES_PATH "A:/home/one/"
#define RESOURCES_PATH "/home/one/"

static void scroll_x_anim_cb(void *obj, int32_t v)
{
    lv_obj_scroll_to_x(obj, v, LV_ANIM_OFF);
}

static bool animation_running = false;
static lv_obj_t *animation_container = NULL;

void demo_widgets(void)
{
    lv_demo_widgets();
    lv_demo_widgets_start_slideshow();
}

#define MAX_IMAGES 6
#define PNG_IMAGES 3
#define JPG_IMAGES 2

void toggle_scroll_animation_event_cb(lv_event_t * e);
void toggle_scroll_animation_event_cb(lv_event_t * e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *container = lv_event_get_user_data(e);
    lv_obj_t *btn_label = lv_obj_get_child(btn, 0);

    if (animation_running) {
        lv_anim_delete(container, scroll_x_anim_cb);
        animation_running = false;
        lv_label_set_text(btn_label, "SCROLL ON");
    } else {
        int32_t content_width = lv_obj_get_scroll_right(container);

        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, container);
        lv_anim_set_exec_cb(&a, scroll_x_anim_cb);
        lv_anim_set_values(&a, 0, content_width);
        lv_anim_set_duration(&a, 20000);
        lv_anim_set_playback_duration(&a, 20000);
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
        lv_anim_set_path_cb(&a, lv_anim_path_linear);

        lv_anim_start(&a);
        animation_running = true;
        animation_container = container;
        lv_label_set_text(btn_label, "SCROLL OFF");
    }
}

void demo_scroll(void)
{
    lv_font_t *roboto_font = lv_freetype_font_create(RESOURCES_PATH "Roboto-Bold.ttf", LV_FREETYPE_FONT_RENDER_MODE_BITMAP, 96, LV_FREETYPE_FONT_STYLE_NORMAL);
    if (!roboto_font) {
        printf("Failed to load Roboto font!\n");
        return;
    }

    lv_obj_t *screen = lv_screen_active();


    lv_obj_t *container = lv_obj_create(screen);
    lv_obj_set_size(container, LV_HOR_RES, LV_VER_RES - 0);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_ON);
    lv_obj_set_scroll_dir(container, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(container, LV_SCROLL_SNAP_NONE);
    lv_obj_align(container, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_set_style_pad_all(container, 0, 0);
    lv_obj_set_style_pad_column(container, 0, 0);

    for (int i = 0; i < MAX_IMAGES; ++i)
    {
        lv_obj_t *img = lv_image_create(container);
        char image_path[100];
        if (i < PNG_IMAGES) {
            snprintf(image_path, sizeof(image_path), LVGL_RESOURCES_PATH "image_%d.png", i + 1);
        } else if (i < PNG_IMAGES + JPG_IMAGES) {
            snprintf(image_path, sizeof(image_path), LVGL_RESOURCES_PATH "image_%d.jpg", i + 1);
        } else {
            snprintf(image_path, sizeof(image_path), LVGL_RESOURCES_PATH "image_%d.svg", i + 1);
        }
        lv_image_set_src(img, image_path);


        lv_obj_t *label = lv_label_create(img);
        char label_text[50];
        snprintf(label_text, sizeof(label_text), "Image %d", i + 1);
        lv_label_set_text(label, label_text);
        lv_obj_set_style_text_font(label, roboto_font, 0);
        if (i != MAX_IMAGES - 1) {
            lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
        } else {
            lv_obj_set_style_text_color(label, lv_color_hex(0x000000), 0);
        }
        lv_obj_center(label);
    }

    // lv_obj_t *btn = lv_button_create(screen);
    // lv_obj_set_size(btn, 600, 80);
    // lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    // lv_obj_add_event_cb(btn, toggle_scroll_animation_event_cb, LV_EVENT_CLICKED, container);

    // lv_obj_t *btn_label = lv_label_create(btn);
    // lv_label_set_text(btn_label, "SCROLL ON");
    // lv_obj_set_style_text_font(btn_label, roboto_font, 0);
    // lv_obj_center(btn_label);
}
