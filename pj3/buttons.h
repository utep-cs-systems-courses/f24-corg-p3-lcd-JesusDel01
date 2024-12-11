#ifndef BUTTONS_H
#define BUTTONS_H

// function to initialize buttons with interrupts
void button_init();
void button1();
// interrupt handler for buttons
void __interrupt_vec(PORT2_VECTOR) Port_2();
void wdt_c_handler();
#endif // BUTTONS_H
