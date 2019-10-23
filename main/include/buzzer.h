#ifndef __buzzer_h_included__
#define __buzzer_h_included__

#define GPIO_BUZZER	25

#define BEEP_INTERVAL_MS	200
#define BEEP_GAP_INTERVAL_MS	200

extern void setup_buzzer();
extern void beep_beep_beep();
extern void long_beep(int milliseconds);

#endif