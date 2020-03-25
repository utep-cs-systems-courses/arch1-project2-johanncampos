#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char state = 0;

void state_advance() {
  switch (state) {
  case 0: //State 0: Home Screen
    red_on = 1;
    green_on ^= 1;
    green_on ? buzzer_set_period(758) : buzzer_set_period(803);
    led_update();
    break;
  case 1: //State 1: Count to Three
    count_to_three();
    led_update();
    break;
  case 2: //State 2: Jump
    jump();
    led_update();
    break;
  case 3: //State 3: Play Calamari Inkantation
    inkantate();
    led_update();
    break;
  case 4: //State 4: 
    break;
  }
}

void count_to_three() {
  //Counter
  static char num = 0;

  //Counting
  switch (num++) {
  case 0: //Start on 0, play C4
    red_on = 0; green_on = 0; buzzer_set_period(7644); break;
  case 1: //Go to 1, play E4
    red_on ^= 1; buzzer_set_period(6067); break;
  case 2: //Go to 2, play G4
    red_on ^= 1; green_on ^= 1; buzzer_set_period(5102); break;
  case 3: //End on 3, play C5
    red_on ^= 1; buzzer_set_period(3822); break;
  }
  
  //Reset after 3
  if (num == 4) {
    num = 0;
  }
}

void jump() {
  
}

void inkantate() {
  //Verses
  static int dooo_do[] = {E4, E4, 0, D4};
  static int scoop[] = {E4, D4, B3, D4};
  static int mount[] = {E4, G4, A4, B4};
  static int end1[] = {A4, 0, A4, G4};
  static int end2[] = {E4, 0, E4, G4};
  static int end3[] = {A4, B4, D5, B4};
  static int end4[] = {A4, G4, E4, D4};
  static int end5[] = {E4, 0, 0, 0};

  //Markers
  static char i = 0;
  static char verse = 0;

  //Current note
  int note = 0;

  //Get next note in song
  switch (verse) {
  case 0: case 4: case 7: (i == 0) ? (red_on = 0, green_on = 1) : 0; //Reset for each return
  case 1: case 2: case 5: case 8: case 9:
    note = dooo_do[i];
    if (i == 0) {//Red and green take turns every second note change
      red_on ^= 1;
      green_on ^= 1;
    }
    break;
  case 3: case 10: //Green handles scoop
    red_on = 0;
    green_on ^= 1;
    note = scoop[i];
    break;
  case 6: green_on = 0; case 11:
    red_on ^= 1; //Red handles mount
    note = mount[i];
    break;
  case 12:
    red_on = 1; //Both come in
    green_on = 1;
    note = end1[i];
    break;
  case 13:
    red_on = 0; //Both go out
    green_on = 0;
    note = end2[i];
    break;
  case 14:
    red_on ^= 1; //Red flickers
    note = end3[i];
    break;
  case 15:
    green_on ^= 1; //Green flickers
    note = end4[i];
    break;
  case 16:
    red_on = 1; //Both come in
    green_on = 1;
    note = end5[i];
    break;
  }

  //Play note
  buzzer_set_period(note);
  
  //Go to next note
  ++i;
  if (i == 4) { //Go to next verse
    i = 0;
    (verse == 16) ? (state = 0, verse = 0) : ++verse; //Exit state when song is finished
  }
}
