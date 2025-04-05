SET(SOURCES screens/ui_Home_Scr.c
    screens/ui_FrontSensorScreen.c
    screens/ui_RadioScreen.c
    screens/ui_HVACScreen.c
    screens/ui_ACControlScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_841796653.c
    images/ui_img_hvac_background_280x205_png.c
    images/ui_img_defrost_16x16_png.c
    images/ui_img_hvac_vents_240x205_png.c)

add_library(ui ${SOURCES})
