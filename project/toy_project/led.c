#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

void led_init() {
  P1DIR = LEDS;
  led_changed = 1;
  led_update();
}

void led_update() {
  if (led_changed) {
    char ledFlags = 0;

    if (red_on) {ledFlags |= LED_RED;}
    if (green_on) {ledFlags |= LED_GREEN;}

    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;

    led_changed = 0;
  }
}
