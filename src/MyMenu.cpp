#include "globals.h"
#include "StateMachine.h"
#include "MyMenu.h"
#include <map>
#define MainMenuSize 4
#define SetupMenuSize 8
#define notPossible [](){return false;}


struct StateTransition
{
  State* initialState;
  bool (*forwardFuction)();
  bool (*backwardFuction)();
  State* endState;

};

struct MenuArrays
{
  String outputString;
  State* stateIndex;
};


StateMachine machine = StateMachine();
State *S_Menu = machine.addState(&MenuM);
State *S_Intervall = machine.addState(&intervall);
State *S_nrOfShots = machine.addState(&nrOfShots);
State *S_confirmMenu = machine.addState(&confirmMenu);
State *S_runningMenu = machine.addState(&runMenu);
State *S_delayMenu = machine.addState(&delayMenu);
State *S_SetupMenu = machine.addState(&SetupMenu);
State *S_ReleaseTime = machine.addState(&releaseTime);
State *S_AutoFocusTime = machine.addState(&autoFocusTime);
State *S_StdDelayTime = machine.addState(&stdDelayTime);
State *S_delayFlag = machine.addState(&delayFlag);
State *S_dispFlipped = machine.addState(&displayFlipped);
State *S_SafeConfig = machine.addState(&safeConfig);
State *S_shootMenu = machine.addState(&shootMenu);
State *S_Pause = machine.addState(&pause);
State *S_ChangeNrofShots = machine.addState(&changeNrofShots);
State *S_Flashlight = machine.addState(&flashlight);
State *S_RampIntervall = machine.addState(&rampIntervall);



MenuArrays setupMenuItems[] {
  {"ReleaseTime",S_ReleaseTime},
  {"AutofocusTime",S_AutoFocusTime},
  {"DelayFlag",S_delayFlag},
  {"DelayTimeStd",S_StdDelayTime},
  {"Displayflipped",S_dispFlipped},
  {"Save Settings",S_SafeConfig}
  };
  
uint8_t sizeofSetup = (sizeof(setupMenuItems)/sizeof(MenuArrays));


StateTransition stateTable[] ={
//inital        forwardFct        backFct                 NextState
{S_Intervall ,  &transShortClick,   &transLongClick,      S_nrOfShots},
{S_Intervall,   &transDoubleClick,  notPossible,          S_Menu},
{S_nrOfShots,   &transShortClick,   &transLongClick,      S_confirmMenu},
{S_nrOfShots,   &transDoubleClick,  notPossible,          S_Menu},
{S_confirmMenu, &transShortClick,   notPossible,          S_runningMenu},
{S_confirmMenu, &transDoubleClick,  notPossible,          S_Menu},
{S_runningMenu, &transShortClick,   notPossible,          S_shootMenu},
{S_runningMenu, &transDoubleClick,  notPossible,          S_Menu},
{S_SetupMenu,   notPossible,        &transDoubleClick,    S_Menu}
};

void defineTransitionsAuto(){
  for(auto elem:stateTable){
     elem.initialState->addTransition(elem.forwardFuction, elem.endState);
     elem.endState->addTransition(elem.backwardFuction,elem.initialState);
  }
}

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

  dM_SetupMenu_neu(
    setupMenuItems[((MenuCounter + sizeofSetup - 1) % sizeofSetup)].outputString,
    setupMenuItems[(MenuCounter % sizeofSetup)].outputString,
    setupMenuItems[((MenuCounter + sizeofSetup + 1) % sizeofSetup)].outputString
  );
  selectedMenu = setupMenuItems[MenuCounter % sizeofSetup].stateIndex->index;
}



void delayMenu()
{

  dM_DelayTime();
  delay_s = MenuCounter;
}

void intervall()
{

  dM_Intervall();
  interval = MenuCounter;
}

void nrOfShots()
{

  dM_NoOfShots();
  shots = MenuCounter * 10;
}

void confirmMenu()
{

  dM_Confirm();
}

void runMenu()
{
  cameraTrigger();
  switch(MenuCounter%3){
    case 0: //mR_fullInfo:
    dm_mR_fullInfo();
    break;
    case 1:
    dm_mR_minInfo();
    break;
    case 2:
    dm_mR_oneDot();
    break;
  }
}

void shootMenu()
{
universalFrame("Shootmenu","Shoot","");
}

void releaseTime()
{
  universalFrame("Releasetime",String(cfg.releaseTime),"ms");
}

void autoFocusTime()
{
  universalFrame("Autofocustime",String(cfg.autofocusTime),"ms");
}

void stdDelayTime()
{
  universalFrame("StdDelay",String(cfg.delayTimeStandard),"");
}

void safeConfig()
{
  universalFrame("SafeConfig","Yes","");
}

void pause()
{
  universalFrame("Pause","Yes","");
}

void changeNrofShots()
{
}

void flashlight()
{
}

void rampIntervall()
{
}

void delayFlag()
{
universalFrame("DelayFlag",String(cfg.delayFlag),"");
}
void displayFlipped()
{
 universalFrame("Flip display",String(cfg.displayflipped),""); 
}






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
      return false;
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

bool transLongClick(){
  if(prevState)
  {
    prevState = false;
    return true;
  }
  return false;
}

bool transDoubleClick(){
  if(doubleClick)
  {
    doubleClick=false;
    return true;
  }
  return false;
}