#include <msp430.h>
#include "bird.h"
#include "led.h"
#include "smallBird.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

extern char lives;
static short start = 0;
static short pause = 0;
static char cycle = 0;
static char button1 = 0;
static char button4 = 0;

#define CYCLE_THRESHOLD 30

void button_init() {
  P2DIR &= ~(BIT0 | BIT1 | BIT3);  //set buttons as inputs
  P2REN |= (BIT0 | BIT1 | BIT3);   //enable pull-up/pull-down resistors
  P2OUT |= (BIT0 | BIT1 | BIT3);   //configure as pull-up resistors
  P2IE  |= (BIT0 | BIT1 | BIT3);   //enable interrupts
  P2IES |= (BIT0 | BIT1 | BIT3);   //interrupt on falling edge
  P2IFG &= ~(BIT0 | BIT1 | BIT3);  //clear interrupt flags
}

void wdt_c_handler() {
  if (start) {
    if (lives > 0) {                      //game continues if lives are positive
      if (!pause) {
        cycle++;
        if (cycle > CYCLE_THRESHOLD) {
          cycle = 0;
          moveSmallBird();                //move small bird
        }
      } else if (button1) {               //button 1 pressed
        cycle++;
        buzzer_set_period(2000);
        turn_on_green_led();
        if (cycle >= CYCLE_THRESHOLD) {
          cycle = 0;
          pause = 0;
          button1 = 0;
          buzzer_set_period(0);
          P1OUT &= ~BIT0;
        }
      } else if (button4) {               //button 4 pressed
        cycle++;
        buzzer_set_period(2000);
        turn_on_red_led();
        if (cycle >= CYCLE_THRESHOLD) {
          cycle = 0;
          pause = 0;
          button4 = 0;
          buzzer_set_period(0);
          P1OUT &= ~BIT6;
        }
      }
    } else { 
      start = 0;                                                         //stop the game
      fillCircle(smallBird.x, smallBird.y, smallBird.size, COLOR_CYAN);
      clearBird();
      fillRectangle(10, 90, 110, 15, COLOR_BLUE);
      drawString8x12(13, 93, "GAME OVER :(", COLOR_WHITE, COLOR_BLUE);
    }
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & BIT0) {                           //button 1
    P2IFG &= ~BIT0;
    pause = 1;
    button1 = 1;
    moveBird(1);
  }
  if (P2IFG & BIT1) {                           //button 2
    P2IFG &= ~BIT1;
    start = 1;                                  //start the game if it hasnt started already
    fillRectangle(20, 90, 93, 15, COLOR_CYAN);  //remove the "2 to STart block"
  }
  if (P2IFG & BIT3) {                           //button 4
    P2IFG &= ~BIT3;
    pause = 1;
    button4 = 1;
    moveBird(-1);
  }
}

void __interrupt_vec(WDT_VECTOR) WDT() {
  wdt_c_handler();
}
