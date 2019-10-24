#ifndef __switches_h_included__
#define __switches_h_included__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define INCREMENT_DECREMENT_SECONDS			60	/* when up / down buttons are pressed, we add this + or - seconds */
#define INCREMENT_DECREMENT_SPEED_UP_AFTER_MS		1000	/* incrementing or decrementing timer speeds up after this amount of time */

#define GPIO_INPUT_IO_0     39 /* Switch #1 */
#define GPIO_INPUT_IO_1	    34 /* Switch #2 */
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))
#define ESP_INTR_FLAG_DEFAULT 0

extern int SWITCH_1_STATE;
extern int SWITCH_2_STATE;

extern void listen_switches(void* arg);
extern void setup_switches();

#endif
