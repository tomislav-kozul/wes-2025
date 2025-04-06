set(COMPONENT_SRCS "user_interface.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES lvgl driver gpio_led gui comms pins front_sensor speaker)

register_component()