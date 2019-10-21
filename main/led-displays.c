#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "include/led-displays.h"
#include "include/switches.h"

int CONTINUITY_CHECK = 0;

void setup_led_displays()
{
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
}

