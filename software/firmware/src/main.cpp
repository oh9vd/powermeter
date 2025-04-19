#include <Arduino.h>

//#define DEBUG  // if this line is NOT commented, these macros will be included in the sketch

#include "debug.h"
#include "adc.h"
#include "calc.h"
#include "time.h"
#include "display.h"
#include "model.h"
#include "enc.h"
#include "freq.h"
#include "info.h"
#include "rssi.h"
#include "datalogger.h"

Model model;
Adc adc(model);
Calc calc(model);
Display disp(model);
Enc enc(model);
Freq freq(model);
Info info(model);
Rssi rssi(model);
Time time(model);
DataLogger logger(model);

// the setup function runs once when you press reset or power the board
void setup()
{
  //debug_init(); // initialize the debugger
  // breakpoint();   // stop execution here
  Serial.begin(57600);

  Wire.begin();

  model.init();
  disp.init();
  time.init();
  rssi.init();
  adc.init();
  calc.init();
  enc.init();
  freq.init();
  info.init();
}

// the loop function runs over and over again until power down or reset
void loop()
{
  enc.loop();
  rssi.loop();
  adc.loop();
  if (model.isSignalPresent())
  {
    freq.loop();
    calc.loop();
    logger.loop();
  } else if (model.but) {
    model.clear();
  }
  time.loop();
  disp.loop();
}

