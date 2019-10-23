#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "include/led-displays.h"
#include "include/switches.h"
#include "include/common.h"
#include "include/tm1637.h"

int CONTINUITY_CHECK = 0;
tm1637_led_t *led;

void setup_led_displays()
{
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    led = tm1637_init(27, 26);
    tm1637_set_brightness(led, 2);
}

void render_timer_display() {

    int digit1 = 0;
    int digit2 = 0;
    int digit3 = 0;
    int digit4 = 0;

    if (timerSeconds < 0 || timerSeconds > 5999) {
	// 5999 seconds: 99 minutes and 59 seconds - max interval that can be displayed on tm1637
	return;
    }

    int minutes = floor(timerSeconds / 60);
    int seconds = timerSeconds % 60;

    if (minutes < 10) {
	digit1 = 0;
	digit2 = minutes;
    } else {
	digit1 = floor(minutes / 10);
	digit2 = minutes % 10;
    }

    if (seconds < 10) {
	digit3 = 0;
	digit4 = seconds;
    } else {
	digit3 = floor(seconds / 10);
	digit4 = seconds % 10;
    }

    tm1637_set_segment_number(led, 0, digit1, false);
    tm1637_set_segment_number(led, 1, digit2, true);
    tm1637_set_segment_number(led, 2, digit3, false);
    tm1637_set_segment_number(led, 3, digit4, false);
}

void erase_timer() {
    tm1637_set_segment_raw(led, 0, 0x00);
    tm1637_set_segment_raw(led, 1, 0x00);
    tm1637_set_segment_raw(led, 2, 0x00);
    tm1637_set_segment_raw(led, 3, 0x00);
}