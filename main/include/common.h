#ifndef __timer_common_h_included__
#define __timer_common_h_included__

#define START_COUNTDOWN_AFTER_MS	5000

/* Value of timer displaed on 4x7 segment display */
/*
    In the launch phase (when setting timer +5 minutes and -5 minutes), this
    value will also change.
 */
extern int timerSeconds;

extern int is_counting_down;
extern int milliseconds_since_last_timer_set;

#endif