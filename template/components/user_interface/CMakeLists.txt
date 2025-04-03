set(COMPONENT_SRCS "user_interface.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES driver gpio_led gpio_button comms)

register_component()