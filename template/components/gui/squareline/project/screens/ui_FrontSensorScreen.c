// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: esp32_gui

#include "../ui.h"

void ui_FrontSensorScreen_screen_init(void)
{
    ui_FrontSensorScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_FrontSensorScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_FrontSensorScreen, lv_color_hex(0x3E3E3E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_FrontSensorScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_frontSensorRedZone = lv_obj_create(ui_FrontSensorScreen);
    lv_obj_remove_style_all(ui_frontSensorRedZone);
    lv_obj_set_width(ui_frontSensorRedZone, 189);
    lv_obj_set_height(ui_frontSensorRedZone, 28);
    lv_obj_set_x(ui_frontSensorRedZone, 2);
    lv_obj_set_y(ui_frontSensorRedZone, -16);
    lv_obj_set_align(ui_frontSensorRedZone, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_frontSensorRedZone, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_frontSensorRedZone, lv_color_hex(0xEE0404), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_frontSensorRedZone, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_frontSensorYellowZone = lv_obj_create(ui_FrontSensorScreen);
    lv_obj_remove_style_all(ui_frontSensorYellowZone);
    lv_obj_set_width(ui_frontSensorYellowZone, 209);
    lv_obj_set_height(ui_frontSensorYellowZone, 27);
    lv_obj_set_x(ui_frontSensorYellowZone, 1);
    lv_obj_set_y(ui_frontSensorYellowZone, -52);
    lv_obj_set_align(ui_frontSensorYellowZone, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_frontSensorYellowZone, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_frontSensorYellowZone, lv_color_hex(0xFFFD0C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_frontSensorYellowZone, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fontSensorGreenZone = lv_obj_create(ui_FrontSensorScreen);
    lv_obj_remove_style_all(ui_fontSensorGreenZone);
    lv_obj_set_width(ui_fontSensorGreenZone, 226);
    lv_obj_set_height(ui_fontSensorGreenZone, 32);
    lv_obj_set_x(ui_fontSensorGreenZone, -1);
    lv_obj_set_y(ui_fontSensorGreenZone, -90);
    lv_obj_set_align(ui_fontSensorGreenZone, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_fontSensorGreenZone, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_fontSensorGreenZone, lv_color_hex(0x4AF43E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_fontSensorGreenZone, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_frontSensorImage = lv_img_create(ui_FrontSensorScreen);
    lv_img_set_src(ui_frontSensorImage, &ui_img_841796653);
    lv_obj_set_width(ui_frontSensorImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_frontSensorImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_frontSensorImage, 23);
    lv_obj_set_y(ui_frontSensorImage, 181);
    lv_obj_set_align(ui_frontSensorImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_frontSensorImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_frontSensorImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}
