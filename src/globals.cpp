#ifndef GLOBALS_H
#define GLOBALS_H
#include "Arduino.h"
#include "eepromData.h"
#include <string.h>
#include "globals.h"





uint16_t MenuCounter=0;
uint8_t Lvl=0;
uint8_t previousState=0;

bool startFlag=0;
unsigned long previousMillis=0;


uint8_t ActionCounter=0;
uint8_t confirm=0;
bool enableMenuCounter=0;


uint8_t skip=0;
bool loadMenuCounter=0;
//uint16_t callcounter=0;
//unsigned long  lastcalled=0;


bool nextState=0;



String SetupMenuItems[]={"Fotosize","ReleaseTime","AutofocusTime","DelayFlag","DelayTimeStd","Displayflipped","Save Settings","Back"};
int sizeofSetup = (sizeof(SetupMenuItems)/sizeof(String));

typedef void (*Menu)(void);
typedef void (*Funktionen)(void);


const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;  // value read from the pot



bool shootFlag = false;
long shoottimepoint =0;
int choosed_Menu = 0;
enum choosenMenu {e_TimelapseM=0,e_TLBulbAstro=20,e_SingleExposure=40,e_Setup=60};
enum MenuStructure {
  mainMenu=0,mainMenuconfirm=1,
  //IntervallMenu
  mI_delayTime_s=2, mI_delayTime_m=3, mI_delayTime_h=4, mI_interval=5,mI_noofShot=6,mI_confirm=7,mI_running =8,
  //SingleExposure
  mSE_delayTime_s=10, mSE_delayTime_m=11, mSE_delayTime_h=12,mSE_exposure=13, mSe_countdown=14,mSE_running =15,
  //TLBulbAstro
  mIA_delayTime_s=20, mIA_delayTime_m=21, mIA_delayTime_h=22,mIA_interval=23,mIA_noofShot=24, mIA_confirm=25,mIA_running=26,
  //Setup
  mS_Setup=30,//Reserviert bis 49
  mS_flashlight=66, mS_Memory=67,
  //Running
  mR_fullInfo =50, mR_minInfo =51,mR_oneDot=52,
  //Abgebrochen
  m_Abgebrochen=255
  
  };

  ///////////////////////////////////////////////
// Settings for Timelapse,Delay,etc
uint8_t delay_h=0;
uint8_t delay_m=0;
uint8_t delay_s=0;
float interval=10;
unsigned long shots=20;
unsigned long shotCount=0;

uint8_t mem_delay_h=0;
uint8_t mem_delay_m=0;
uint8_t mem_delay_s=0;
float mem_interval=1;
uint16_t mem_shots=0;
uint16_t releasetime =200;

configData_t cfg;
/////////////////////////////////////////////////////////////////


// Menu menus[][5] = {
// {dM_TimelapseM, dM_DelayTime, dM_Intervall, dM_NoOfShots },
// {dM_TLBulbAstro, dM_DelayTime, dM_Intervall, dM_NoOfShots},
// {dM_SingleExposure, dM_DelayTime, dM_Exposure, dM_DelayCountDown,dm_Start},
// {dM_Setup, dM_DelayTime, dM_Intervall, dM_NoOfShots}
// };
//uint8_t MenuLen = (sizeof(menus[0]) / sizeof(Menu));

#endif 