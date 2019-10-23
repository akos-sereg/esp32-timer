#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/buzzer.h"

void setup_buzzer() {
    gpio_set_direction(GPIO_BUZZER, GPIO_MODE_OUTPUT);
}

void beep_beep_beep() {
    int i = 0;

    for (i=0; i!=3; i++) {
	gpio_set_level(GPIO_BUZZER, 1);
	vTaskDelay(BEEP_INTERVAL_MS / portTICK_RATE_MS);
	gpio_set_level(GPIO_BUZZER, 0);
	vTaskDelay(BEEP_GAP_INTERVAL_MS / portTICK_RATE_MS);
    }
}

void long_beep(int milliseconds) {
    gpio_set_level(GPIO_BUZZER, 1);
    vTaskDelay(milliseconds / portTICK_RATE_MS);
    gpio_set_level(GPIO_BUZZER, 0);
}