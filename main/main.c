#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/timer-state.h"
#include "include/led-displays.h"
#include "include/switches.h"
#include "include/buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

void app_main()
{
    int tick_rate_ms = 100;
    int elapsed_ms_in_second = 0;
    int elapsed_ms_in_5seconds = 0;
    int elapsed_ms_up_pressed = 0;
    int elapsed_ms_down_pressed = 0;

    setup_led_displays();
    setup_switches();
    setup_buzzer();

    render_timer_display();

    while(1) {
        vTaskDelay(tick_rate_ms / portTICK_RATE_MS);

	// manage up / down buttons
	if (SWITCH_1_STATE && !is_counting_down) {
	    elapsed_ms_up_pressed += tick_rate_ms;
	    if (elapsed_ms_up_pressed > INCREMENT_DECREMENT_SPEED_UP_AFTER_MS) {
		add_timer_seconds(60);
	    }
	} else {
	    elapsed_ms_up_pressed = 0;
	}

	if (SWITCH_2_STATE && !is_counting_down) {
	    elapsed_ms_down_pressed += tick_rate_ms;
	    if (elapsed_ms_down_pressed > INCREMENT_DECREMENT_SPEED_UP_AFTER_MS) {
		add_timer_seconds(-60);
	    }
	} else {
	    elapsed_ms_down_pressed = 0;
	}

	// manage countdown clock:
	// start / stop / countdown
	if (is_counting_down == 0) {
	    milliseconds_since_last_timer_set += tick_rate_ms;
	}

	if (milliseconds_since_last_timer_set >= START_COUNTDOWN_AFTER_MS && timer_seconds > 0) {
	    beep_beep_beep(1);
	    milliseconds_since_last_timer_set = 0;
	    is_counting_down = 1;
	}

	elapsed_ms_in_second += tick_rate_ms;
	if (is_counting_down && elapsed_ms_in_second >= 1000) {
	    if (timer_seconds > 0) {
		timer_seconds--;
		elapsed_ms_in_second = 0;
		render_timer_display();
	    }

	    if (timer_seconds == 0) {
		long_beep(TIME_UP_BEEP_MS);
		is_counting_down = 0;
		gpio_set_level(GPIO_LED, 0);
	    }
	}

	// flash light
	if (is_counting_down) {
	    if (elapsed_ms_in_5seconds == 0) {
		gpio_set_level(GPIO_LED, 0);
	    }
	    elapsed_ms_in_5seconds += tick_rate_ms;
	    if (elapsed_ms_in_5seconds >= 5000) {
		gpio_set_level(GPIO_LED, 1);
		elapsed_ms_in_5seconds = 0;
	    }
	}
    }
}

