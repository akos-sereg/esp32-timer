#ifndef __buzzer_h_included__
#define __buzzer_h_included__

#define GPIO_BUZZER	25

#define BEEP_INTERVAL_MS	150
#define BEEP_GAP_INTERVAL_MS	150
#define TIME_UP_BEEP_MS		3000

extern void setup_buzzer();
extern void beep_beep_beep(int hide_display_in_gaps);
extern void long_beep(int milliseconds);

#endif