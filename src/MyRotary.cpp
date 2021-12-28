#include "MyRotary.h"

ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);
uint16_t callcounter=0;
unsigned long  lastcalled =0;


void initRotory(){
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(rotateLeft);
  r.setRightRotationHandler(rotateRight);

  b.setClickHandler(click);
  b.setLongClickHandler(resetPosition);
  b.setDoubleClickHandler(doubleclick);
  pinMode(ROTARY_GND,OUTPUT); //GND
  digitalWrite(D8,LOW);
  pinMode(ROTARY_VCC,OUTPUT); //+
  digitalWrite(D7,HIGH);
}
// on change
void rotate(ESPRotary& r) {
  
   Serial.print("Position: ");
   Serial.println(r.getPosition());

}

// on left or right rotation



 
// single click
void click(Button2& btn) {
  Serial.println("Click!");

  Lvl++;
  //MenuCounter=0;
  loadMenuCounter=true;
  nextState=1;

}

// long click
void resetPosition(Button2& btn) {
  //r.resetPosition();
  //Serial.println("Reset!");
  MenuCounter=0;
  loadMenuCounter=true;
  if(Lvl==2){
    Lvl=0;
  }else{
    Lvl--;

     confirm--;
  }
  if(startFlag == true){
    startFlag=false;
    Lvl=255;
  }
 
}

void rotateLeft(ESPRotary& r){
  Serial.println("Millsdiff:" + String(millis()-lastcalled)+ " MC:" + String(MenuCounter)+" ");
  
switch(millis()-lastcalled){

  case 1 ... 35: MenuCounter=MenuCounter-11; Serial.print("10erCout"); break;
  case 36 ... 100:MenuCounter=MenuCounter-4; Serial.print("4erCout");break;
  default:  MenuCounter--;Serial.print("normalCount"); break;
}
  

  lastcalled=millis();
}

void rotateRight(ESPRotary& r){
 
switch(millis()-lastcalled){

  case 1 ... 35: MenuCounter=MenuCounter+11; Serial.print("10erCout"); break;
  case 36 ... 100:MenuCounter=MenuCounter+4; Serial.print("4erCout");break;
  default:  MenuCounter++;Serial.print("normalCount"); break;
}
  

  lastcalled=millis();
}
    
    

  
  


void showDirection(ESPRotary& r) {
  Serial.println(r.directionToString(r.getDirection()));
}

void doubleclick(Button2& btn){
 skip++;
}

void skipFunc(uint8_t LvlRaise){
  if(skip>0){
  Lvl=Lvl+LvlRaise;
  skip=0;
  }
}
  
