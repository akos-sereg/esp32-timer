#include "include/switches.h"
#include "include/led-displays.h"
#include "include/timer-state.h"
#include "include/buzzer.h"

int SWITCH_1_STATE = 0;
int SWITCH_2_STATE = 0;

static xQueueHandle gpio_evt_queue = NULL;

int64_t get_epoch_milliseconds();

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void listen_switches(void* arg)
{
    uint32_t io_num;
    int current_state;
    int64_t current_epoch;

    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
	    vTaskDelay(50 / portTICK_RATE_MS);
	    if (is_counting_down == 1) {
		// user input is no longer considered - eg. we are in countdown mode, and
		// we should not be responding on increment / decrement timer.
		continue;
	    }

	    current_state = gpio_get_level(io_num);

	    if (io_num == GPIO_INPUT_IO_0 && SWITCH_1_STATE != current_state) {
		SWITCH_1_STATE = current_state;
		if (current_state == 1) {
		    // raising edge: up botton has just been pressed
		    long_beep(100);
		    add_timer_seconds(INCREMENT_DECREMENT_SECONDS);
		}
	    }

	    if (io_num == GPIO_INPUT_IO_1 && SWITCH_2_STATE != current_state) {
		SWITCH_2_STATE = current_state;
		if (current_state == 1) {
		    // raising edge: down button has just been pressed

		    current_epoch = get_epoch_milliseconds();
		    if (current_epoch < 2000) {
		        // in case "down" button is pressed within 2 seconds after startup, we are
		        // in silent mode
		        silent_mode = 1;
		    }

		    long_beep(100);
		    add_timer_seconds(-INCREMENT_DECREMENT_SECONDS);
		}
	    }
        }
    }
}

void setup_switches()
{
    gpio_config_t io_conf;

    //disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;

    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;

    //interrupt of rising edge
    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;

    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;

    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;

    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(GPIO_INPUT_IO_1, GPIO_INTR_ANYEDGE);

    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    //start gpio task
    xTaskCreate(listen_switches, "listen_switches", 8192 * 5, NULL, 5, NULL);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
    gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void*) GPIO_INPUT_IO_1);

    //remove isr handler for gpio number.
    gpio_isr_handler_remove(GPIO_INPUT_IO_0);
    gpio_isr_handler_remove(GPIO_INPUT_IO_1);

    //hook isr handler for specific gpio pin again
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
    gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void*) GPIO_INPUT_IO_1);
}

int64_t get_epoch_milliseconds() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}