#include "MyRotary.h"
//#include <WiFiUdp.h>
//#include "WiFiManager.h"  
#include <ArduinoOTA.h>
#include"MyOLED.h"
#include <EEPROM.h>
#include "eepromData.h"
#include "main.h"

#define cfgStart 0
#define CamOutput D3

/////////////////////////////////////////////////////////////////
//Globals



typedef void (*Menu)(void);
typedef void (*Funktionen)(void);

Menu menus[][5] = {
{dM_TimelapseM, dM_DelayTime, dM_Intervall, dM_NoOfShots },
{dM_TLBulbAstro, dM_DelayTime, dM_Intervall, dM_NoOfShots},
{dM_SingleExposure, dM_DelayTime, dM_Exposure, dM_DelayCountDown,dm_Start},
{dM_Setup, dM_DelayTime, dM_Intervall, dM_NoOfShots}
};

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;  // value read from the pot
bool startFlag = false;
uint16_t MenuCounter = 0;
uint8_t ActionCounter = 0;
uint8_t skip =0;
bool enableMenuCounter = true;
uint8_t Lvl=0;
uint8_t previousState=0;
uint8_t confirm=0;
bool loadMenuCounter=0;
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

uint8_t MenuLen = (sizeof(menus[0]) / sizeof(Menu));
unsigned long previousMillis = 0;

String SetupMenuItems[]={"Fotosize","ReleaseTime","AutofocusTime","DelayFlag","DelayTimeStd","Displayflipped","Save Settings","Back"};
int sizeofSetup = (sizeof(SetupMenuItems)/sizeof(String));

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

void setup() {
  EEPROM.begin(4096);
  Serial.begin(9600);
  Serial.println("Online");
  initRotory();
// WiFiManager wifiManager;  
// wifiManager.resetSettings();          //mit diesem befehl kannst die gespeicherten werte löschen              
//wifiManager.autoConnect("UHR");
  Serial.println("verbunden!");
  ArduinoOTA.setHostname("TLaps_OTA");
  ArduinoOTA.setPassword("Beffy");
  ArduinoOTA.begin();
  Serial.println(WiFi.localIP());
    display.init();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  enableMenuCounter = true;
  Lvl=0;
  Serial.println("setupLVL:"+String(Lvl));
  pinMode(CamOutput,OUTPUT);
  digitalWrite(CamOutput,HIGH);
  
  //eepromTest();
  loadConfig();
  shootFlag =false;
}

void DevelopmentInfo(){
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(12, 0, String(int(millis())/1000));
//  display.drawString(12, 12, String(analogRead(analogInPin)*0.015)+"V");
//  Serial.println(String(analogRead(analogInPin)*0.015)+"V");
  
  
  // write the buffer to the display
  
  //display.drawString(110,48,"Mc: " + String(MenuCounter%MenuLen));
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(48,48,"L: " + String(Lvl)+"M:" + String(MenuCounter)+"A:" + String(ActionCounter)+"C:" + String(confirm));
  //eepromTest();
  //loadConfig();

}


void savePreviousState(){
 previousState =Lvl;
}

void loadMC(uint16_t Value){
if(loadMenuCounter){
MenuCounter=Value;
loadMenuCounter=false;
          }
}

void loadMC(uint16_t Value, float factor){
if(loadMenuCounter){
MenuCounter=uint16_t(Value/factor);
loadMenuCounter=false;
          }
}

void timeSetup(){
  if(delay_s>=60){
    delay_s=0;
    delay_m++;
  }
    if(delay_m>=60){
    delay_m=0;
    delay_h++;
  }
    if(delay_s<=0){
    delay_s=60;
    if(delay_m!=0){
      delay_m--;
    }
    
  }
}

String SeperateTimehms( unsigned long seconds){
unsigned short   tage     = seconds         / 86400;
unsigned short stunden  = seconds % 86400 /  3600;
unsigned short  minuten  = seconds %  3600 /    60;
unsigned short sekunden = seconds %    60        ;
if (seconds>=60){
  return String(minuten)+"``"+String(sekunden);
}else if(seconds>=3600){
  return String(stunden)+"`"+String(minuten)+"``"+ String(sekunden);
}else if(seconds>=86400){
  return String(tage)+"d"+String(stunden)+"`"+String(minuten)+"``"+String(sekunden);
}else{
  return "``"+String(sekunden);
}
}


void delay_disabled(){
  if(cfg.delayFlag==false){
    if(Lvl==mI_delayTime_h or Lvl==mSE_delayTime_h or Lvl==mIA_delayTime_h){
      Lvl=Lvl-4;
    }else{
    Lvl=Lvl+3;
  }
}
}
void menuControl2(){
    switch(Lvl){
      case mainMenu:    
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
            }break;
      case mainMenuconfirm:    
            switch(MenuCounter%4){
            case 0 :// dM_TimelapseM
              dM_TimelapseM();
              Lvl=2;
              //delay_disabled();
              break;
            case 1 :        
              dM_TLBulbAstro();
              Lvl=20;
              //delay_disabled();
              break;
            case 2 :        
              dM_SingleExposure();
              Lvl=10;
              //delay_disabled();
              break;
            case 3 :
              dM_Setup();
              Lvl=mS_Setup;
                   
              break;
            }break;
      case mI_delayTime_s: case mSE_delayTime_s: case mIA_delayTime_s:
             if(cfg.delayFlag==false){
              Lvl=Lvl+3;
             }else{
             skipFunc(3);
             dM_DelayTime();
             loadMC(delay_s);
             delay_s=MenuCounter;
             //timeSetup();
             }
             break;
      case mI_delayTime_m:case mSE_delayTime_m: case mIA_delayTime_m:
             skipFunc(2);
             dM_DelayTime();
             loadMC(delay_m);
             delay_m=MenuCounter;
             //timeSetup();
             break;
      case mI_delayTime_h:case mSE_delayTime_h: case mIA_delayTime_h:
              if(cfg.delayFlag==false){
              Lvl=Lvl-4;
             }else{
             skipFunc(1);
             //delay_disabled();
             dM_DelayTime();
             loadMC(delay_h);
             delay_h=MenuCounter;
             //timeSetup();
             }
             break;
    
      case mI_interval: case mIA_interval:             
             dM_Intervall();
             loadMC(interval);
             interval=MenuCounter;
             break;
      case mI_noofShot: case mIA_noofShot:
             dM_NoOfShots();
             loadMC(shots,10);
             shots=MenuCounter*10;
             break;
      case mI_confirm: case mIA_confirm:
             dM_Confirm();
             break;
      case mI_running: case mSE_running: case mIA_running:
          startFlag = true;
          break;

      case mS_Setup:
        dM_SetupMenu();
        break;


        
      case m_Abgebrochen:
        dM_Abgebrochen();
        shotCount=0;
        break;
  }
}

void cameraTrigger(){
  
  // do this every interval only
  if ( ( millis() - previousMillis ) >=   (interval*100) ) {

    if ( ( shots != 0 ) && ( shotCount >= shots ) ) { // sequence is finished
      // stop shooting
      //isRunning = 0;
      //currentMenu = SCR_DONE;
      //lcd.clear();
      //printDoneScreen(); // invoke manually
      //stopShooting();
      Lvl=0;
      startFlag = false;
      shotCount=0;
    } else { // is running
      //runningTime += (millis() - previousMillis );
      previousMillis = millis();
      shootFlag=true;
      shotCount++;
    }
  }

  // do this always (multiple times per interval)
 // possiblyRampInterval();
}

void  runningMenu(){
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



void releaseCamera(){
  if(shootFlag){
    shoottimepoint=millis();
    digitalWrite(CamOutput,LOW);
    shootFlag = false;
  }else{
    if(millis()-shoottimepoint >= releasetime){
      digitalWrite(CamOutput,HIGH);
    }
  }
 // digitalWrite(CamOutput,LOW);
  //delay(releasetime);
      //digitalWrite(CamOutput,HIGH);
}

void loop() {
enableMenuCounter =true;
  ArduinoOTA.handle();
  // clear the display
  display.clear();
  // draw the current demo method
 // MenuLen = (sizeof(menus[MenuCounter%4]) / sizeof(Menu));
 // menus[MenuCounter%4][Lvl%MenuLen]();
 if (startFlag){

  runningMenu();
  
 }else{
    menuControl2();
 }

  DevelopmentInfo(); // wird ausgeschaltet
  //menus[0]();
//digitalWrite(12, LOW);
  display.display();
  r.loop();
  b.loop();
  releaseCamera();
}

void eepromTest(){
  
  cfg.valid=1; // 0=no configuration, 1=valid configuration
  cfg.fotoSize=25;
  cfg.releaseTime=100;
  cfg.autofocusTime=200;
  cfg.delayFlag=false; //delay =0 delaymenu off 1=on
  cfg.delayTimeStandard = 2;
  cfg.displayflipped =true;
  saveConfig();
  Serial.println("Saved Eprom");
}


////////////////////////////////EEPROM Functions/////////////////////////////////



void loadConfig() {
  // Loads configuration from EEPROM into RAM
  EEPROM.begin(4095);
  EEPROM.get( cfgStart, cfg );
  EEPROM.end();
  Serial.println("cfg.autofocusTime");
  Serial.println(cfg.autofocusTime);
}

void saveConfig() {
  // Save configuration from RAM into EEPROM
  EEPROM.begin(4095);
  EEPROM.put( cfgStart, cfg );
  delay(200);
  EEPROM.commit();                      // Only needed for ESP8266 to get data written
  EEPROM.end(); 
  // Free RAM copy of structure
}


/////////////////////////////////////////////////////////////////
