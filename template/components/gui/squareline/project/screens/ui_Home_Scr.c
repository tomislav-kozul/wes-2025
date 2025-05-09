// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: esp32_gui

#include "../ui.h"

void ui_Home_Scr_screen_init(void)
{
    ui_Home_Scr = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home_Scr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Home_Scr, lv_color_hex(0x111111), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Home_Scr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button3 = lv_btn_create(ui_Home_Scr);
    lv_obj_set_width(ui_Button3, 100);
    lv_obj_set_height(ui_Button3, 50);
    lv_obj_set_x(ui_Button3, 22);
    lv_obj_set_y(ui_Button3, -81);
    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_text_color(ui_Button3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Button3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Button3);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "jebeno");

    ui_Label3 = lv_label_create(ui_Home_Scr);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 113);
    lv_obj_set_y(ui_Label3, -94);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Counter:");
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPressCounter = lv_label_create(ui_Home_Scr);
    lv_obj_set_width(ui_ButtonPressCounter, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ButtonPressCounter, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ButtonPressCounter, 107);
    lv_obj_set_y(ui_ButtonPressCounter, -68);
    lv_obj_set_align(ui_ButtonPressCounter, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ButtonPressCounter, "0");
    lv_obj_set_style_text_color(ui_ButtonPressCounter, lv_color_hex(0xFF00F2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ButtonPressCounter, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_radioButton = lv_btn_create(ui_Home_Scr);
    lv_obj_set_width(ui_radioButton, 100);
    lv_obj_set_height(ui_radioButton, 50);
    lv_obj_set_x(ui_radioButton, -91);
    lv_obj_set_y(ui_radioButton, -4);
    lv_obj_set_align(ui_radioButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_radioButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_radioButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label4 = lv_label_create(ui_radioButton);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Radio");

    ui_hvacButton = lv_btn_create(ui_Home_Scr);
    lv_obj_set_width(ui_hvacButton, 100);
    lv_obj_set_height(ui_hvacButton, 50);
    lv_obj_set_x(ui_hvacButton, 27);
    lv_obj_set_y(ui_hvacButton, -4);
    lv_obj_set_align(ui_hvacButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_hvacButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_hvacButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label5 = lv_label_create(ui_hvacButton);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "HVAC");

    ui_frontSensorButton = lv_btn_create(ui_Home_Scr);
    lv_obj_set_width(ui_frontSensorButton, 147);
    lv_obj_set_height(ui_frontSensorButton, 50);
    lv_obj_set_x(ui_frontSensorButton, -31);
    lv_obj_set_y(ui_frontSensorButton, 63);
    lv_obj_set_align(ui_frontSensorButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_frontSensorButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_frontSensorButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_frontSensorButton);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Front Sensor");

    lv_obj_add_event_cb(ui_Button3, ui_event_Button3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_radioButton, ui_event_radioButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_hvacButton, ui_event_hvacButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_frontSensorButton, ui_event_frontSensorButton, LV_EVENT_ALL, NULL);

}
