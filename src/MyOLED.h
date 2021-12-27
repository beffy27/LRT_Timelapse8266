#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"




extern SSD1306Wire display;





void drawTextFlowDemo();

String twoDigits(int digits);
void dM_TimelapseM();
void dM_TLBulbAstro();
void dM_SingleExposure();
void dM_Setup();
void dM_DelayTime();
void dM_Intervall();
void dM_NoOfShots();
void dM_Exposure();
void dM_DelayCountDown();
void dm_Start();
void dM_Confirm();
void  dm_mR_fullInfo();
void  dm_mR_minInfo();
void  dm_mR_oneDot();
String SeperateTimehms( unsigned long seconds);
void releaseCamera();
void dM_Abgebrochen();
void dM_SetupMenu();
