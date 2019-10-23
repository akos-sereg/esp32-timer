#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/buzzer.h"
#include "include/led-displays.h"

void setup_buzzer() {
    gpio_set_direction(GPIO_BUZZER, GPIO_MODE_OUTPUT);
}

void beep_beep_beep(int hide_display_in_gaps) {
    int i = 0;

    for (i=0; i!=3; i++) {
	// beep
	beep_on();
	if (hide_display_in_gaps) {
	    render_timer_display();
	}
	vTaskDelay(BEEP_INTERVAL_MS / portTICK_RATE_MS);

	// gap
	beep_off();
	if (hide_display_in_gaps) {
	    erase_timer();
	}
	vTaskDelay(BEEP_GAP_INTERVAL_MS / portTICK_RATE_MS);
    }

    if (hide_display_in_gaps) {
	render_timer_display();
    }
}

void long_beep(int milliseconds) {
    beep_on();
    vTaskDelay(milliseconds / portTICK_RATE_MS);
    beep_off();
}

void beep_on() {
    if (BUZZER_ENABLED) {
	gpio_set_level(GPIO_BUZZER, 1);
    }
}

void beep_off() {
    gpio_set_level(GPIO_BUZZER, 0);
}