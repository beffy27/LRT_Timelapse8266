#ifndef MYMENU_H
#define MYMENU_H

#include <Arduino.h>
//#include "MyRotary.h"
//#include "MyOLED.h"





//States
/**
 * @brief is the mainMenu state
 * transitions are:
 * -trans_Menu_Setup
 */
void MenuM();

/**
 * @brief is the setup menu state
 * 
 * transitions are:
 * trans_Setup_Menu
 */
void SetupMenu();

/**
 * @brief is the delay Menu state
 * 
 */
void delayMenu();

/**
 * @brief select the interval menu
 * 
 */
void intervall();

/**
 * @brief select number of shots
 * 
 */
void nrOfShots();

/**
 * @brief this is the confirmation menu
 * 
 */
void confirmMenu();

/**
 * @brief the running menu chose of 3 different modi
 * 
 */
extern void runMenu();

/**
 * @brief shooting menu where you can place e.g ramp intervall
 * 
 */
void shootMenu();


//Transitions

bool trans_Menu_Setup();

bool trans_Setup_Menu();

bool transShortClick();

bool transLongClick();

bool transDoubleClick();


//Funktions
void defineTransitions();

void runMenuStatemachine();




#endif
