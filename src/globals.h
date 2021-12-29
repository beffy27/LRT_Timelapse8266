#ifndef GLOBALS_H
#define GLOBALS_H
#include "Arduino.h"
#include "eepromData.h"
#include <string.h>



extern uint16_t MenuCounter;
extern uint16_t selectedMenu;
extern uint8_t Lvl;
extern uint8_t previousState;
extern bool startFlag;
extern unsigned long previousMillis;
extern uint8_t ActionCounter;
extern uint8_t confirm;
extern bool enableMenuCounter;
extern uint8_t skip;
extern bool loadMenuCounter;
extern bool nextState;

extern String SetupMenuItems[];
extern int sizeofSetup;

extern const int analogInPin;  // ESP8266 Analog Pin ADC0 = A0
extern int sensorValue;  // value read from the pot
extern bool shootFlag;
extern long shoottimepoint;
extern int choosed_Menu;
//extern enum MenuStructure;


  ///////////////////////////////////////////////
// Settings for Timelapse,Delay,etc
extern uint8_t delay_h;
extern uint8_t delay_m;
extern uint8_t delay_s;
extern float interval;
extern unsigned long shots;
extern unsigned long shotCount;
extern uint8_t mem_delay_h;
extern uint8_t mem_delay_m;
extern uint8_t mem_delay_s;
extern float mem_interval;
extern uint16_t mem_shots;
extern uint16_t releasetime;

extern configData_t cfg;
/////////////////////////////////////////////////////////////////

extern void dM_TimelapseM();
extern void dM_TLBulbAstro();
extern void dM_SingleExposure();
extern void dM_Setup();
extern void dM_DelayTime();
extern void dM_Intervall();
extern void dM_NoOfShots();
extern void dM_Exposure();
extern void dM_DelayCountDown();
extern void dm_Start();
extern void dM_Confirm();
extern void dm_mR_fullInfo();
extern void dm_mR_minInfo();
extern void dm_mR_oneDot();
extern void releaseCamera();
extern void dM_Abgebrochen();
extern void dM_SetupMenu();

typedef void (*Menu)(void);
typedef void (*Funktionen)(void);
extern Menu menus[][5];
extern uint8_t MenuLen;

#endif 