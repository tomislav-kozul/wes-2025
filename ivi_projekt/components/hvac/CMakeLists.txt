set(COMPONENT_SRCS "hvac.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES comms gpio_led pins)

register_component()