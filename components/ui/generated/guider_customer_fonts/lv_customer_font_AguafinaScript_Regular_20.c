/*
 * Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/
/*******************************************************************************
 * Size: 20 px
 * Bpp: 4
 * Opts: undefined
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_CUSTOMER_FONT_AGUAFINASCRIPT_REGULAR_20
#define LV_CUSTOMER_FONT_AGUAFINASCRIPT_REGULAR_20 1
#endif

#if LV_CUSTOMER_FONT_AGUAFINASCRIPT_REGULAR_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0077 "w" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x0, 0xb,
    0x40, 0x5b, 0x3, 0xe3, 0x0, 0x7d, 0x0, 0xe5,
    0x3f, 0x80, 0x0, 0xe6, 0x7, 0xd0, 0xdc, 0x0,
    0x5, 0xf0, 0x1e, 0x72, 0xe1, 0x53, 0xb, 0x90,
    0xaf, 0x14, 0x96, 0x20, 0x1f, 0x46, 0xbc, 0x24,
    0x0, 0x0, 0x6f, 0x92, 0xec, 0x60, 0x0, 0x0,
    0xaf, 0x32, 0xfa, 0x0, 0x0, 0x0, 0xb3, 0x4,
    0x90, 0x0, 0x0, 0x0,

    /* U+0078 "x" */
    0x0, 0x0, 0x3e, 0x10, 0x5e, 0x20, 0x0, 0x3,
    0xf1, 0x75, 0x11, 0x0, 0x0, 0x3f, 0x81, 0x0,
    0x0, 0x0, 0x5, 0xf0, 0x0, 0x2, 0x0, 0x3,
    0xdf, 0x0, 0x4, 0x30, 0x4, 0x97, 0xf0, 0x3,
    0x30, 0x5, 0xa0, 0x7f, 0x3, 0x40, 0x5, 0xd0,
    0x7, 0xfa, 0x30, 0x0, 0x73, 0x0, 0x4d, 0x30,
    0x0, 0x0,

    /* U+007A "z" */
    0x0, 0x0, 0x2, 0xa9, 0x6a, 0x90, 0x0, 0x0,
    0xb, 0x50, 0xbe, 0x20, 0x0, 0x0, 0x22, 0x2d,
    0xd2, 0x0, 0x0, 0x0, 0x4, 0xec, 0x10, 0x0,
    0x0, 0x0, 0x6f, 0xb0, 0x0, 0x0, 0x0, 0x8,
    0xfb, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xb0, 0x1a,
    0x0, 0x0, 0x7, 0xfc, 0x1, 0xc7, 0x0, 0x0,
    0x2f, 0xfa, 0x9e, 0xb0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 148, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 106, .box_w = 11, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 105, .box_w = 12, .box_h = 9, .ofs_x = -2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 1, 0, 2
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 119, .range_length = 4, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_customer_font_AguafinaScript_Regular_20 = {
#else
lv_font_t lv_customer_font_AguafinaScript_Regular_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
};



#endif /*#if LV_CUSTOMER_FONT_AGUAFINASCRIPT_REGULAR_20*/

