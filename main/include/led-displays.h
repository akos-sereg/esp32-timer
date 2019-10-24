#ifndef __led_displays_h_included__
#define __led_displays_h_included__

#define GPIO_LED		33
#define DISPLAY_PAD_ZERO	0   /* enabled: "9:12", disabled: "09:12" */

extern void setup_led_displays();    /* setup tm1637 module */
extern void render_timer_display();  /* render timer_seconds on display */
extern void erase_timer();           /* make display blank */

#endif