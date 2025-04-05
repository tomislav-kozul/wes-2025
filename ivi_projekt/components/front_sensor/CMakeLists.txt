set(COMPONENT_SRCS "front_sensor.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES driver pins comms ultrasonic)

register_component()