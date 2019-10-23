#include "include/timer-state.h"
#include "include/led-displays.h"

int timer_seconds = 0;
int milliseconds_since_last_timer_set = 0;
int is_counting_down = 0;

void add_timer_seconds(int seconds) {
    timer_seconds += seconds;

    if (timer_seconds < 0) {
	timer_seconds = 0;
    }

    if (timer_seconds > 5999) {
	// 5999 is 99:59, the maximum time that can be displayed on tm1637
	timer_seconds = 5999;
    }

    milliseconds_since_last_timer_set = 0;
    render_timer_display();
}