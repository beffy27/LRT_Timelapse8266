#include "globals.h"
#include "StateMachine.h"
void MenuM(){
  switch(MenuCounter%4){
            case 0 :// dM_TimelapseM
              dM_TimelapseM();
              break;
            case 1 :        
              dM_TLBulbAstro();
              break;
            case 2 :        
              dM_SingleExposure();
              break;
            case 3 :        
              dM_Setup();
              break;
            }
}

void SetupMenu(){
  dM_SetupMenu();
}

bool trans_Menu_Setup(){
  if(MenuCounter%4==3 && nextState){
    nextState=false;
    return true;
  }
  return false;
}

bool trans_Setup_Menu(){
  if(MenuCounter%sizeofSetup==7 && nextState){
    nextState=false;
    return true;
  }else{
  return false;
  }
}

StateMachine machine = StateMachine();
State* S_Menu = machine.addState(&MenuM);
State* S_SetupMenu = machine.addState(&SetupMenu);

void defineTransitions(){
S_Menu->addTransition(&trans_Menu_Setup,S_SetupMenu);
S_SetupMenu->addTransition(&trans_Setup_Menu,S_Menu);
}

void runMenuStatemachine(){
    machine.run();
};