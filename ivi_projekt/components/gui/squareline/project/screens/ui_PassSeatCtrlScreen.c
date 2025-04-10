// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: esp32_gui

#include "../ui.h"

void ui_PassSeatCtrlScreen_screen_init(void)
{
    ui_PassSeatCtrlScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_PassSeatCtrlScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PassSeatCtrlScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PassSeatCtrlScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_PassSeatCtrlScreen, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PassSeatCtrlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PassSeatCtrlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PassSeatCtrlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PassSeatCtrlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image4 = lv_img_create(ui_PassSeatCtrlScreen);
    lv_img_set_src(ui_Image4, &ui_img_seats_pass_240x180_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image4, 23);
    lv_obj_set_y(ui_Image4, 23);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image4, 300);
    lv_obj_set_style_img_recolor(ui_Image4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Image4, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_currentTimePass = lv_label_create(ui_PassSeatCtrlScreen);
    lv_obj_set_width(ui_currentTimePass, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_currentTimePass, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_currentTimePass, -135);
    lv_obj_set_y(ui_currentTimePass, -100);
    lv_obj_set_align(ui_currentTimePass, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_currentTimePass, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_currentTimePass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_currentTimePass, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_currentDatePass = lv_label_create(ui_PassSeatCtrlScreen);
    lv_obj_set_width(ui_currentDatePass, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_currentDatePass, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_currentDatePass, 3);
    lv_obj_set_y(ui_currentDatePass, -101);
    lv_obj_set_align(ui_currentDatePass, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_currentDatePass, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_currentDatePass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ambientTemperatureLabelPass = lv_label_create(ui_PassSeatCtrlScreen);
    lv_obj_set_width(ui_ambientTemperatureLabelPass, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ambientTemperatureLabelPass, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ambientTemperatureLabelPass, -9);
    lv_obj_set_y(ui_ambientTemperatureLabelPass, 9);
    lv_obj_set_align(ui_ambientTemperatureLabelPass, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_ambientTemperatureLabelPass, "°C");
    lv_obj_set_style_text_color(ui_ambientTemperatureLabelPass, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ambientTemperatureLabelPass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ambientTemperatureLabelPass, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HomeButtonPass = lv_btn_create(ui_PassSeatCtrlScreen);
    lv_obj_set_width(ui_HomeButtonPass, 50);
    lv_obj_set_height(ui_HomeButtonPass, 50);
    lv_obj_set_x(ui_HomeButtonPass, -135);
    lv_obj_set_y(ui_HomeButtonPass, -57);
    lv_obj_set_align(ui_HomeButtonPass, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HomeButtonPass, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_HomeButtonPass, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_HomeButtonPass, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_HomeButtonPass, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HomeButtonPass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_HomeButtonPass, &ui_img_home32_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_HomeButtonPass, lv_color_hex(0xA3A3A3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_HomeButtonPass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_HomeButtonPass, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_HomeButtonPass, ui_event_HomeButtonPass, LV_EVENT_ALL, NULL);

}
