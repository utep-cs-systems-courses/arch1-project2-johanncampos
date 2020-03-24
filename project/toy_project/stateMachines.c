#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void state_advance() {
  /*
    static char num = 0;
    switch (num) {
    case 0: case 2: red_on ^= 1; break;
    case 1: case 3: red_on ^= 1; break;
    }
    ++num;
    if (num == 4) {
      num = 0;
    }
  */
  led_changed = 1;
  led_update();
}
