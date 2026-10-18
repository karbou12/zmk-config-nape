/*
 * Copyright (c) 2026 Tano Karbou (github: karbou12 / X: @karbou_12)
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include <zmk/events/trackball_angle_changed.h>
#include <zmk_rgbled_widget/widget.h>

LOG_MODULE_REGISTER(nape_trackball_rgb, CONFIG_ZMK_LOG_LEVEL);

static const enum zmk_rgbled_widget_color angle_colors[] = {
    ZMK_RGBLED_WIDGET_COLOR_WHITE,
    ZMK_RGBLED_WIDGET_COLOR_YELLOW,
    ZMK_RGBLED_WIDGET_COLOR_CYAN,
    ZMK_RGBLED_WIDGET_COLOR_MAGENTA,
    ZMK_RGBLED_WIDGET_COLOR_GREEN,
    ZMK_RGBLED_WIDGET_COLOR_BLUE,
    ZMK_RGBLED_WIDGET_COLOR_RED,
    ZMK_RGBLED_WIDGET_COLOR_GREEN,
};

static int trackball_angle_changed_listener_cb(const zmk_event_t *eh) {
    const struct zmk_trackball_angle_changed *event = as_zmk_trackball_angle_changed(eh);
    if (event == NULL) {
        return 0;
    }

    const uint16_t shifted_angle_in_direction = event->angle_deg + (uint16_t)(CONFIG_ZMK_TRACKBALL_SHIFT_DIRECTION_ANGLE_DEG / 2);
    const uint16_t device_direction_index = shifted_angle_in_direction / CONFIG_ZMK_TRACKBALL_SHIFT_DIRECTION_ANGLE_DEG;
    const uint8_t color_index = (uint8_t)(device_direction_index % ARRAY_SIZE(angle_colors));
    const uint8_t blink_count = 3;
    const int ret = zmk_rgbled_widget_blink_color(angle_colors[color_index], blink_count);
    if (ret != 0) {
        LOG_ERR("Failed to queue trackball angle LED indication: %d", ret);
    }

    return 0;
}

ZMK_LISTENER(trackball_angle_changed_listener, trackball_angle_changed_listener_cb);
ZMK_SUBSCRIPTION(trackball_angle_changed_listener, zmk_trackball_angle_changed);
