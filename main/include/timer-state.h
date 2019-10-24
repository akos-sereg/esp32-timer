#ifndef __timer_state_h_included__
#define __timer_state_h_included__

#define START_COUNTDOWN_AFTER_MS	5000	/* timeout: if no up / down button pressed for a while, we start the countdown automatically */

extern int timer_seconds;    /* seconds displayed on tm1637 display - all the times: in "set" mode, and in "countdown" mode as well */
extern int is_counting_down; /* indicates if device is in "countdown" mode or in "set" mode */
extern int milliseconds_since_last_timer_set; /* if we are in "set" mode, this is the time elapsed since we received user input */

extern void add_timer_seconds(int seconds); /* in "set" mode, add number of seconds to timer_seconds, update display, etc */

#endif