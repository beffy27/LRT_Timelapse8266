#ifndef eepromData_h
#define eepromData_h

#include <WString.h>

typedef struct {


  int valid; // 0=no configuration, 1=valid configuration
  uint16_t fotoSize;
  uint16_t releaseTime;
  uint16_t autofocusTime;
  bool delayFlag; //delay =0 delaymenu off 1=on
  uint16_t delayTimeStandard;
  bool displayflipped;
  
  
  
} configData_t;


#endif
