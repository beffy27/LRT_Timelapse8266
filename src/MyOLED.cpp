#include "MyOLED.h"
#include "MyRotary.h"

SSD1306Wire display(0x3c, D2, D1);
int displayX = 128;
int displayY = 64;
int centerX = displayX / 2;
int centerY = displayY / 2;

String twoDigits(int digits)
{
    if (digits < 10)
    {
        String i = '0' + String(digits);
        return i;
    }
    else
    {
        return String(digits);
    }
}

String intervalToFloat(uint16_t digits)
{
    Serial.print(interval);
    if (digits < 1000)
    {
        String i = '0' + '.' + String(digits / 100);
        return i;
    }
    else
    {
        return String(digits / 1000) + '.' + String(digits / 100);
    }
}

void dM_MainMenu()
{

    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.drawString(centerX, centerY, MenuItems[((MenuCounter + sizeofMenu - 1) % sizeofMenu)]);
}
/*
void dM_TimelapseM(){
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(centerX,centerY,"Timelapse(M)");
}
void dM_TLBulbAstro(){
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(centerX,centerY,"TL Bulb Astro");  
}
void dM_SingleExposure(){
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(centerX,centerY,"SingleExposure");  
}
void dM_Setup(){
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(centerX,centerY,"Setup");  
}
*/
void dM_DelayTime()
{
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX, 5, "DelayTime");
    display.drawString(centerX, 54, "Skip (DoubleClick)");
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.setFont(ArialMT_Plain_24);
    display.drawString(centerX, centerY, String(delay_h) + "h" + twoDigits(delay_m) + "m" + twoDigits(delay_s) + "s");
}
void dM_Intervall()
{
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX, 5, "Intervall");
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.setFont(ArialMT_Plain_24);
    display.drawString(centerX, centerY, String(float(interval / 10)) + "s");
}
void dM_NoOfShots()
{
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX, 5, "No. Shots");
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.setFont(ArialMT_Plain_24);
    display.drawString(centerX, centerY, String(shots) + " Pics");
}
void dM_Confirm()
{
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX - 60, 5, "Int: " + String(float(interval / 10)) + "s");
    display.drawString(centerX - 60, 15, "Del: " + String(delay_h) + "h" + twoDigits(delay_m) + "m" + twoDigits(delay_s) + "s");
    display.drawString(centerX - 60, 25, "Shots: " + String(shots));
    display.drawString(centerX - 60, 35, "Time: " + SeperateTimehms((shots * (long)interval / 10)));
}

void universalFrame(String headline,String displayed_var, String unit){
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX, 5, headline);
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.setFont(ArialMT_Plain_24);
    display.drawString(centerX, centerY, displayed_var +" "+ unit);
}

void dM_Abgebrochen()
{
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.drawString(centerX, centerY, "Abgebrochen");
}
void dM_Exposure()
{
}
void dM_DelayCountDown()
{
}

void dm_Start()
{
}
void dM_SetupMenu()
{
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(centerX, centerY - 10, SetupMenuItems[(MenuCounter % sizeofSetup)]);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX, centerY - 30, SetupMenuItems[((MenuCounter + sizeofSetup - 1) % sizeofSetup)]);
    display.drawString(centerX, centerY + 16, SetupMenuItems[((MenuCounter + sizeofSetup + 1) % sizeofSetup)]);
}

void dM_SetupMenu_neu(String before, String main, String after)
{
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(centerX, centerY - 10, main);
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX, centerY - 30, before);
    display.drawString(centerX, centerY + 16, after);
}

void dm_mR_fullInfo()
{
    display.setFont(ArialMT_Plain_24);
    display.drawString(centerX - 36, 20, String(shotCount));
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX + 20, 25, "R: " + String(shots - shotCount));
    display.drawString(centerX + 60, 1, "T: " + SeperateTimehms((shotCount * (long)interval / 10)));
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(centerX, 49, "I:" + String(interval / 10) + "s");
    display.drawString(centerX + 60, 49, "T-: " + SeperateTimehms((long)(shots - shotCount) * interval / 10));
}
void dm_mR_minInfo()
{
    display.setFont(ArialMT_Plain_10);
    display.drawString(centerX - 40, 1, String(shotCount));
    display.drawString(centerX + 20, 1, "T: " + SeperateTimehms(shots * interval / 10));
}

void dm_mR_oneDot()
{
    if (shotCount % 2)
    {
        display.setPixel(1, 1);
    }
}
