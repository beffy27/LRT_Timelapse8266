#ifndef MAIN_H
#define MAIN_H
#include "globals.h"
extern void loadConfig();

extern void saveConfig();
extern void defineTransitions();
extern void runMenuStatemachine();
extern uint16_t MenuCounter;
extern bool nextState;

#endif // MAIN_H