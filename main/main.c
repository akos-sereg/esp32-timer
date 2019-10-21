#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/led-displays.h"
#include "include/switches.h"
#include "include/tm1637.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

void app_main()
{
    int cnt = 0;

    setup_led_displays();
    setup_switches();

    while(1) {
        vTaskDelay(500 / portTICK_RATE_MS);

	// flash light
	gpio_set_level(GPIO_LED, cnt % 2);
	printf("Flash: %d\n", cnt % 2);

	cnt++;
	if (cnt == 60000) cnt = 0;
    }
}

