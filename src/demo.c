#include <stdio.h>

#include "demo.h"

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#define RESOURCES_PATH "A:/projects/lvgl/lv_port_linux/src/resources/"

void demo_widgets(void)
{
    lv_demo_widgets();
    lv_demo_widgets_start_slideshow();
}

#define MAX_IMAGES 6
#define PNG_IMAGES 3
#define JPG_IMAGES 2
lv_obj_t* img[MAX_IMAGES] = {NULL};

void demo_scroll(void)
{
    lv_obj_t *screen = lv_screen_active();

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
        img[i] = lv_image_create(container);  /* Add images to container, not screen */
        char image_path[100];
        if (i < PNG_IMAGES) {
            snprintf(image_path, sizeof(image_path), RESOURCES_PATH "image_%d.png", i + 1);
        } else if (i < PNG_IMAGES + JPG_IMAGES) {
            snprintf(image_path, sizeof(image_path), RESOURCES_PATH "image_%d.jpg", i + 1);
        } else {
            snprintf(image_path, sizeof(image_path), RESOURCES_PATH "image_%d.svg", i + 1);
        }
        lv_image_set_src(img[i], image_path);
    }
}
