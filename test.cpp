/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// #include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/*
  Connect button so that pressing the switch connects the GPIO 9 (default) to ground (pull down)
*/

#define BUTTON_GPIO 9

int main()
{
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	gpio_init(BUTTON_GPIO);
	gpio_set_dir(BUTTON_GPIO, GPIO_IN);
	// We are using the button to pull down to 0v when pressed, so ensure that when
	// unpressed, it uses internal pull ups. Otherwise when unpressed, the input will
	// be floating.
	gpio_pull_up(BUTTON_GPIO);

	while (true) {
		// Count upwards or downwards depending on button input
		// We are pulling down on switch active, so invert the get to make
		// a press count downwards
		gpio_put(PICO_DEFAULT_LED_PIN, !gpio_get(BUTTON_GPIO));
		sleep_ms(50);
	}

	return 0;
}
