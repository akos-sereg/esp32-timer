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
	gpio_set_level(GPIO_BUZZER, 1);
	if (hide_display_in_gaps) {
	    render_timer_display();
	}
	vTaskDelay(BEEP_INTERVAL_MS / portTICK_RATE_MS);

	// gap
	gpio_set_level(GPIO_BUZZER, 0);
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
    gpio_set_level(GPIO_BUZZER, 1);
    vTaskDelay(milliseconds / portTICK_RATE_MS);
    gpio_set_level(GPIO_BUZZER, 0);
}