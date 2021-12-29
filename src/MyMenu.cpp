#include "globals.h"
#include "StateMachine.h"

#define MainMenuSize 4
#define SetupMenuSize 8

// Menus
void MenuM()
{
  selectedMenu = 1;
  switch (MenuCounter % 4)
  {
  case 0: // dM_TimelapseM
    dM_TimelapseM();
    break;
  case 1:
    dM_TLBulbAstro();
    break;
  case 2:
    dM_SingleExposure();
    break;
  case 3:
    dM_Setup();
    break;
  }
}

void SetupMenu()
{
  selectedMenu = 2;
  dM_SetupMenu();
}

void delayMenu()
{
  selectedMenu = 0;
  dM_DelayTime();
  delay_s = MenuCounter;
}

void intervall()
{
  selectedMenu = 0;
  dM_Intervall();
  interval = MenuCounter;
}

void nrOfShots()
{
  selectedMenu = 0;
  dM_NoOfShots();
  shots = MenuCounter * 10;
}

void confirmMenu()
{
  selectedMenu = 0;
  dM_Confirm();
}

// void runningMenu()
// {
//   selectedMenu = 0;
// }

// Functions

bool trans_Menu_Setup()
{
  if (MenuCounter % MainMenuSize == 3 && nextState)
  {
    nextState = false;
    return true;
  }
  return false;
}

bool trans_Setup_Menu()
{
  if (MenuCounter % sizeofSetup == 7 && nextState)
  {
    nextState = false;
    return true;
  }
  else
  {
    return false;
  }
}

bool transShortClick()
{
  if (selectedMenu)
  {
    if (MenuCounter % MainMenuSize == selectedMenu && nextState)
    {
      nextState = false;
      return true;
    }
    return false;
  }
  else
  {
    if (nextState)
    {
      nextState = false;
      return true;
    }
    return false;
  }
}

StateMachine machine = StateMachine();
State *S_Menu = machine.addState(&MenuM);
State *S_SetupMenu = machine.addState(&SetupMenu);
State *S_Intervall = machine.addState(&intervall);
State *S_nrOfShots = machine.addState(&nrOfShots);
State *S_confirmMenu = machine.addState(&confirmMenu);
//State *S_runningMenu = machine.addState(&runningMenu);
State *S_delayMenu = machine.addState(&delayMenu);

void defineTransitions()
{
  S_Menu->addTransition(&trans_Menu_Setup, S_SetupMenu);
  S_SetupMenu->addTransition(&trans_Setup_Menu, S_Menu);
  S_Menu->addTransition(&transShortClick, S_Intervall);
  S_Intervall->addTransition(&transShortClick, S_nrOfShots);
  S_nrOfShots->addTransition(&transShortClick, S_confirmMenu);
}

void runMenuStatemachine()
{
  machine.run();
};