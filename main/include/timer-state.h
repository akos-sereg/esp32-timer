#ifndef __timer_state_h_included__
#define __timer_state_h_included__

#define START_COUNTDOWN_AFTER_MS	5000

extern int timer_seconds;
extern int is_counting_down;
extern int milliseconds_since_last_timer_set;

extern void add_timer_seconds(int seconds);

#endif