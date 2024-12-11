#include <msp430.h>
#include <libTimer.h>
#include <stdio.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "background.h"
#include "bird.h"
#include "led.h"
#include "buzzer.h"
#include "buttons.h"
#include "smallBird.h"
#include "buzzer.h"





int main() {
  configureClocks();       // configure the system clock
  lcd_init();              // initialose the board
  init_leds();             // initialized the leds
  button_init();           // initialized the buttons for presses
  buzzer_init();
  buzzer_set_period(0);
  P1OUT &= ~LEDS; 
  enableWDTInterrupts();
  
  clearScreen(COLOR_BLUE); // clear the screen with a blue background
  drawBackground();
  drawBird();
  initSmallBird();
  fillRectangle(20, 90, 93, 15, COLOR_BLUE);
  drawString8x12(23, 93, "2 to START", COLOR_WHITE, COLOR_BLUE);
  fillRectangle(55, 10, 26, 13, COLOR_BLUE);
  drawString8x12(60, 11, "0" , COLOR_WHITE, COLOR_BLUE);
  fillRectangle(3, 10, 13, 13, COLOR_BLUE);
  drawString8x12(5, 11, "3", COLOR_WHITE, COLOR_BLUE);
  or_sr(0x8);

  while (1) {
    or_sr(0x10);
  }  
  return 0;
}

