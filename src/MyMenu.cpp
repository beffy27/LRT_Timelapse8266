#include "globals.h"
#include "StateMachine.h"
#include "MyMenu.h"
#define MainMenuSize 4
#define SetupMenuSize 8


StateMachine machine = StateMachine();
State *S_Menu = machine.addState(&MenuM);
State *S_SetupMenu = machine.addState(&SetupMenu);
State *S_Intervall = machine.addState(&intervall);
State *S_nrOfShots = machine.addState(&nrOfShots);
State *S_confirmMenu = machine.addState(&confirmMenu);
//State *S_runningMenu = machine.addState(&runningMenu);
State *S_delayMenu = machine.addState(&delayMenu);

// Menus
void MenuM()
{
  dM_MainMenu();
  switch (MenuCounter % sizeofMenu)
  {
  case 0:
    selectedMenu = S_SetupMenu->index;
    
    break;
  case 1:
    selectedMenu = S_Intervall->index;
    break;
  case 2:
    selectedMenu = S_delayMenu->index;
    break;
  case 3:
    selectedMenu = S_Intervall->index;
    break;
  }
}

void SetupMenu()
{
  selectable = true;
  dM_SetupMenu();
  if((MenuCounter % sizeofSetup) == (sizeofSetup-1))
  {
  selectedMenu = S_Menu->index;
  }
}

void delayMenu()
{
  selectable = false;
  dM_DelayTime();
  delay_s = MenuCounter;
}

void intervall()
{
  selectable = false;
  dM_Intervall();
  interval = MenuCounter;
}

void nrOfShots()
{
  selectable = false;
  dM_NoOfShots();
  shots = MenuCounter * 10;
}

void confirmMenu()
{
  selectable = false;
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





void defineTransitions()
{
  S_Menu->addTransition(&transShortClick, S_SetupMenu);
  S_SetupMenu->addTransition(&transShortClick, S_Menu);
  // S_Menu->addTransition(&transShortClick, S_Intervall);
  // S_Intervall->addTransition(&transShortClick, S_nrOfShots);
  // S_nrOfShots->addTransition(&transShortClick, S_confirmMenu);
}

void runMenuStatemachine()
{
  machine.run();
};

bool transShortClick()
{
  if (machine.currentState == S_Menu->index or machine.currentState == S_SetupMenu->index)
  {
    if (nextState)
    {
      Serial.println("selectedMenu:" +  String(selectedMenu));
      machine.transitionTo(selectedMenu);
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
