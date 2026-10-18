if(CONFIG_RGBLED_WIDGET AND CONFIG_ZMK_TRACKBALL_SHIFT)
    zephyr_library()
    zephyr_library_sources(src/trackball_angle_rgb.c)
endif()
