#ifndef __buzzer_h_included__
#define __buzzer_h_included__

#define GPIO_BUZZER	25

#define BUZZER_ENABLED		1	/* enable sound */
#define BEEP_INTERVAL_MS	100	/* beep_beep_beep() will use this interval when in beep mode */
#define BEEP_GAP_INTERVAL_MS	100	/* beep_beep_beep() will use this interval when there is no sound */
#define TIME_UP_BEEP_MS		3000	/* when countdown reaches 00:00, beep takes this long */

extern void setup_buzzer();
extern void beep_beep_beep(int hide_display_in_gaps);
extern void long_beep(int milliseconds);
extern void beep_on();
extern void beep_off();

#endif