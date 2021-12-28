#ifndef MYROTARTY_H
#define MYROTARTY_H

/////////////////////////////////////////////////////////////////
#include "Button2.h" //  https://github.com/LennartHennigs/Button2
#include <ESPRotary.h>
#include "globals.h"

/////////////////////////////////////////////////////////////////
#define ROTARY_PIN1  D0
#define ROTARY_PIN2 D5
#define BUTTON_PIN  D6
#define ROTARY_GND D8
#define ROTARY_VCC D7
#define CLICKS_PER_STEP   4  // this number depends on your rotary encoder 

extern ESPRotary r;
extern Button2 b;



void initRotory();
void resetPosition(Button2& btn);
void click(Button2& btn);
void showDirection(ESPRotary& r);
void rotate(ESPRotary& r);
void rotateLeft(ESPRotary& r);
void rotateRight(ESPRotary& r);
void doubleclick(Button2& btn);
void skipFunc(uint8_t LvlRaise);

#endif