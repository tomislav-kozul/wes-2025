set(COMPONENT_SRCS "sht3x.c" "temperature_sensor.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES driver comms)

register_component()