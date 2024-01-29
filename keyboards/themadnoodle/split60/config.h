// Copyright 2023 The Mad Noodle (@The Mad Noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 4
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF