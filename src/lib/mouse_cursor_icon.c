/**
 *
 * @file mouse_cursor_icon.c
 *
 * The C array containing the mouse cursor icon
 *
 * Based on the original file from the repository
 * Copyright (c) 2025 EDGEMTech Ltd.
 *
 * Author: EDGEMTech Ltd, Erik Tagirov (erik.tagirov@edgemtech.ch)
 *
 */
#include "lvgl/lvgl.h"

const uint8_t mouse_cursor_icon_map[] = {
    0x00, 0x00, 0x00, 0x00
};

lv_image_dsc_t mouse_cursor_icon = {
    .header.magic = LV_IMAGE_HEADER_MAGIC,
    .header.w = 1,
    .header.h = 1,
    .header.stride = 4,
    .data_size = 4,
    .header.cf = LV_COLOR_FORMAT_ARGB8888,
    .data = mouse_cursor_icon_map,
};
