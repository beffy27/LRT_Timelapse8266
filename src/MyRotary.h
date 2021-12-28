

/////////////////////////////////////////////////////////////////

#include "Button2.h" //  https://github.com/LennartHennigs/Button2
#include <ESPRotary.h>

/////////////////////////////////////////////////////////////////
#define ROTARY_PIN1  D0
#define ROTARY_PIN2 D5
#define BUTTON_PIN  D6
#define ROTARY_GND D8
#define ROTARY_VCC D7
#define CLICKS_PER_STEP   4  // this number depends on your rotary encoder 

extern ESPRotary r;
extern Button2 b;
extern uint16_t MenuCounter;
extern uint8_t Lvl;
extern uint8_t previousState;
extern uint8_t delay_h;
extern uint8_t delay_m;
extern uint8_t delay_s;
extern float interval;
extern uint8_t mem_delay_h;
extern uint8_t mem_delay_m;
extern uint8_t mem_delay_s;
extern float mem_interval;
extern uint16_t mem_shots;
extern unsigned long shotCount;
extern bool startFlag;
extern unsigned long previousMillis;

extern uint8_t ActionCounter;
extern uint8_t confirm;
extern bool enableMenuCounter;
extern unsigned long shots;
extern int choosed_Menu;
extern uint8_t skip;
extern bool loadMenuCounter;
extern uint16_t callcounter;
extern unsigned long  lastcalled;
extern String SetupMenuItems[];
extern int sizeofSetup;
extern bool nextState;


void initRotory();
void resetPosition(Button2& btn);
void click(Button2& btn);
void showDirection(ESPRotary& r);
void rotate(ESPRotary& r);
void rotateLeft(ESPRotary& r);
void rotateRight(ESPRotary& r);
void doubleclick(Button2& btn);
void skipFunc(uint8_t LvlRaise);
