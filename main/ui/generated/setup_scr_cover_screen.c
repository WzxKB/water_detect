/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_cover_screen(lv_ui *ui)
{
    //Write codes cover_screen
    ui->cover_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->cover_screen, 240, 240);
    lv_obj_set_scrollbar_mode(ui->cover_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for cover_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->cover_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes cover_screen_cont_1
    ui->cover_screen_cont_1 = lv_obj_create(ui->cover_screen);
    lv_obj_set_pos(ui->cover_screen_cont_1, 2, 1);
    lv_obj_set_size(ui->cover_screen_cont_1, 240, 240);
    lv_obj_set_scrollbar_mode(ui->cover_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for cover_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->cover_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->cover_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->cover_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->cover_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->cover_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->cover_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->cover_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->cover_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->cover_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->cover_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->cover_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->cover_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->cover_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes cover_screen_label_2
    ui->cover_screen_label_2 = lv_label_create(ui->cover_screen);
    lv_label_set_text(ui->cover_screen_label_2, "---Wang Yu Xuan");
    lv_label_set_long_mode(ui->cover_screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->cover_screen_label_2, 12, 31);
    lv_obj_set_size(ui->cover_screen_label_2, 110, 45);

    //Write style for cover_screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->cover_screen_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->cover_screen_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->cover_screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->cover_screen_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->cover_screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->cover_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes cover_screen_img_1
    ui->cover_screen_img_1 = lv_img_create(ui->cover_screen);
    lv_obj_add_flag(ui->cover_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->cover_screen_img_1, &_shuidi_alpha_100x111);
    lv_img_set_pivot(ui->cover_screen_img_1, 50,50);
    lv_img_set_angle(ui->cover_screen_img_1, 0);
    lv_obj_set_pos(ui->cover_screen_img_1, 125, 109);
    lv_obj_set_size(ui->cover_screen_img_1, 100, 111);

    //Write style for cover_screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->cover_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->cover_screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->cover_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->cover_screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of cover_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->cover_screen);

}
