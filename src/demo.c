#include <stdio.h>

#include "demo.h"

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#define LVGL_RESOURCES_PATH "A:/projects/lvgl/lv_port_linux/src/resources/"
#define RESOURCES_PATH "/projects/lvgl/lv_port_linux/src/resources/"

void demo_widgets(void)
{
    lv_demo_widgets();
    lv_demo_widgets_start_slideshow();
}

#define MAX_IMAGES 6
#define PNG_IMAGES 3
#define JPG_IMAGES 2

void demo_scroll(void)
{
    lv_obj_t *screen = lv_screen_active();

    lv_font_t *roboto_font = lv_freetype_font_create(RESOURCES_PATH "Roboto-Bold.ttf", LV_FREETYPE_FONT_RENDER_MODE_BITMAP, 96, LV_FREETYPE_FONT_STYLE_NORMAL);
    if (!roboto_font) {
        printf("Failed to load Roboto font!\n");
        return;
    }

    lv_obj_t *container = lv_obj_create(screen);
    lv_obj_set_size(container, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_ON);
    lv_obj_set_scroll_dir(container, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(container, LV_SCROLL_SNAP_CENTER);
    lv_obj_center(container);

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
        lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
        lv_obj_center(label);
    }
}
