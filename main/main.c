#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/common.h"
#include "include/led-displays.h"
#include "include/switches.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

int is_counting_down = 0;
int milliseconds_since_last_timer_set = 0;

void app_main()
{
    int tick_rate_ms = 100;
    int elapsed_ms_in_second = 0;
    int elapsed_ms_in_5seconds = 0;

    setup_led_displays();
    setup_switches();
    render_timer_display();

    while(1) {
        vTaskDelay(tick_rate_ms / portTICK_RATE_MS);

	// manage elapsed time since timer set
	if (is_counting_down == 0) {
	    milliseconds_since_last_timer_set += tick_rate_ms;
	}

	if (milliseconds_since_last_timer_set >= START_COUNTDOWN_AFTER_MS && timerSeconds > 0) {
	    is_counting_down = 1;
	}

	elapsed_ms_in_second += tick_rate_ms;
	if (is_counting_down && elapsed_ms_in_second >= 1000) {
	    if (timerSeconds > 0) {
		timerSeconds--;
		elapsed_ms_in_second = 0;
		render_timer_display();
	    }
	}

	// flash light
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

