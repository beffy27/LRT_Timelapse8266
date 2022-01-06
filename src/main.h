#ifndef MAIN_H
#define MAIN_H
#include "globals.h"
extern void loadConfig();

extern void saveConfig();
extern void defineTransitionsAuto();
extern void runMenuStatemachine();
extern uint16_t MenuCounter;
extern bool nextState;
bool shootFlag =false;
void eepromTest();
void loadConfig(); 
void saveConfig();

#endif // MAIN_H