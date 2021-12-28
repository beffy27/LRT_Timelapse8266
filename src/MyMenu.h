#ifndef MYMENU_H
#define MYMENU_H

#include <Arduino.h>
//#include "MyRotary.h"
//#include "MyOLED.h"





//States
void MenuM();

void SetupMenu();


//Transitions

bool trans_Menu_Setup();

bool trans_Setup_Menu();


//Funktions
void defineTransitions();

void runMenuStatemachine();




#endif
