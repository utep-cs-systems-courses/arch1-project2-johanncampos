#include <msp430.h>
#include "led.h"
#include "stateMachines.h"
#include "switches.h"

char sw1_state_down, sw2_state_down, sw3_state_down, sw4_state_down;

static char switch_update_interrupt_sense() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val & ~SWITCHES);
  return p2val;
}

void switch_init() {
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();

  //Detect button presses
  sw1_state_down = (p2val & SW1) ? 0 : 1;
  sw2_state_down = (p2val & SW2) ? 0 : 1;
  sw3_state_down = (p2val & SW3) ? 0 : 1;
  sw4_state_down = (p2val & SW4) ? 0 : 1;

  if (sw1_state_down) {
    green_on = 0;
    red_on = 0;
  }
  if (sw2_state_down) {
    green_on = 0;
    red_on = 1;
  }
  if (sw3_state_down) {
    green_on = 1;
    red_on = 0;
  }
  if (sw4_state_down) {
    green_on = 1;
    red_on = 1;
  }

  //state_advane();
}
