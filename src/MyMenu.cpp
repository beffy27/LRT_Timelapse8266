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


MenuArrays mainMenuItems[] {
  {"Intervall",S_Intervall},
  {"Setup",S_SetupMenu}
  };
  
uint8_t sizeofMainMenu = (sizeof(mainMenuItems)/sizeof(MenuArrays));


StateTransition stateTable[] ={
//inital          forwardFct        backFct                 NextState
{S_Intervall ,    &transShortClick,   &transLongClick,      S_nrOfShots},
{S_Intervall,     &transDoubleClick,  notPossible,          S_Menu},
{S_nrOfShots,     &transShortClick,   &transLongClick,      S_confirmMenu},
{S_nrOfShots,     &transDoubleClick,  notPossible,          S_Menu},
{S_confirmMenu,   &transShortClick,   notPossible,          S_runningMenu},
{S_confirmMenu,   &transDoubleClick,  notPossible,          S_Menu},
{S_runningMenu,   &transShortClick,   notPossible,          S_shootMenu},
{S_runningMenu,   &transDoubleClick,  notPossible,          S_Menu},
{S_SetupMenu,     notPossible,   &transDoubleClick,    S_Menu},
{S_ReleaseTime,   &transShortClick,   notPossible,          S_Menu},
{S_AutoFocusTime, &transShortClick,   notPossible,          S_Menu},
{S_StdDelayTime , &transShortClick,   notPossible,          S_Menu},
{S_delayFlag,     &transShortClick,   notPossible,          S_Menu},
{S_dispFlipped,   &transShortClick,   notPossible,          S_Menu},
{S_SafeConfig,    &transShortClick,   notPossible,          S_Menu},
{S_Menu,          &transMenuIntervall,   notPossible,          S_Intervall},
{S_Menu,          &transMenuSetup,   notPossible,          S_SetupMenu},
//{S_SetupMenu,     &transSetupMenu,   notPossible,          S_SetupMenu},
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
  Serial.println("Menu"+String(machine.currentState));
  
  universalFrame("",mainMenuItems[(MenuCounter % sizeofMainMenu)].outputString,"");

}

void SetupMenu()
{
  
  dM_SetupMenu_neu(
    setupMenuItems[((MenuCounter + sizeofSetup - 1) % sizeofSetup)].outputString,
    setupMenuItems[(MenuCounter % sizeofSetup)].outputString,
    setupMenuItems[((MenuCounter + sizeofSetup + 1) % sizeofSetup)].outputString
  );
  
  //selectedMenu = setupMenuItems[MenuCounter % sizeofSetup].stateIndex->index;
}



void delayMenu()
{

  dM_DelayTime();
  delay_s = MenuCounter;
}

void intervall()
{
  Serial.println("intervall");
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
  Serial.println("runMenu");
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
  Serial.println("releaseTime");
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


void runMenuStatemachine()
{
  machine.run();

};

bool transShortClick()
{
    Serial.println("next state Short Click");
    Serial.println(machine.currentState);
  /*if (machine.currentState == S_Menu->index)
  {
    if (nextState)
    {
      Serial.println("selectedMenu:" +  String(selectedMenu));
      //machine.transitionTo(selectedMenu);
      S_Menu->addTransition([](){
            S_Menu->setTransition(0,selectedMenu);
            return true;
             },S_Menu);
      nextState = false;
      return true;
    }
    return false;
  }else if(machine.currentState == S_SetupMenu->index){
    if (nextState)
    {
      Serial.println("selectedMenu:" +  String(selectedMenu));
      //machine.transitionTo(selectedMenu);
      S_SetupMenu->addTransition([](){
            S_SetupMenu->setTransition(0,selectedMenu);
            return true;
             },S_SetupMenu);
      nextState = false;
      return true;
    }
    return false;
  }
  else
  {*/
    if (nextState)
    {
      nextState = false;
      Serial.println("true Short Click");
      return true;
    }
    return false;
  //}
}

bool transLongClick(){
  Serial.println("next state LongClick");
  if(prevState)
  {
    prevState = false;
    Serial.println("LongClick true");
    machine.transitionTo(S_Intervall->index);
    return false;
  }
  return false;
}

bool transDoubleClick(){
  Serial.println("next state DoubleClick");
  if(doubleClick)
  {
    doubleClick=false;
    Serial.println("DoubleClick true");
    return true;
  }
  return false;
}

bool transMenuAuswahl(){
  if (nextState && mainMenuItems[(MenuCounter % sizeofMainMenu)].outputString == mainMenuItems[0].outputString)
  {
    nextState = false;
    return true;
  }
  else if (nextState && mainMenuItems[(MenuCounter % sizeofMainMenu)].outputString == mainMenuItems[1].outputString)
  {
    nextState = false;
    return true;
  }
  return false;
}

// bool transSetupMenu(){
//   Serial.println("transSetupMenu "+String(machine.currentState));
//   if(nextState){
//     nextState = false;
//     S_SetupMenu->addTransition([](){
//     Serial.print("Transitioning to Setupstate ");
//     Serial.println(setupMenuItems[(MenuCounter % sizeofSetup)].outputString);
//     Serial.println("cS:"+String(machine.currentState));
//     S_SetupMenu->setTransition(S_SetupMenu->index,setupMenuItems[(MenuCounter % sizeofSetup)].stateIndex->index);
   
//     return true;
//   },S_SetupMenu);
//    Serial.println("cS_after:"+String(machine.currentState));
//   return false;
//   }
//   return false;
// }

bool transMenuIntervall(){
  if(nextState && mainMenuItems[(MenuCounter % sizeofMainMenu)].outputString == mainMenuItems[0].outputString){
    nextState = false;
    return true;
  }
  return false;
}

bool transMenuSetup(){
  if(nextState && mainMenuItems[(MenuCounter % sizeofMainMenu)].outputString == mainMenuItems[1].outputString){
    nextState = false;
    return true;
  }
  return false;
}