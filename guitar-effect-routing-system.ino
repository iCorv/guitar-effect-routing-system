#include "Control.h"


Control myControl;

void setup() {
  Serial.begin(115200);
  //myBank.setLoop(7,true);
  //myBank.savePreset();
  //myBank.printPreset(1);
  myControl.initControl();
}

void loop() {
  // check if switch has changed
  myControl.switchListener();

  switch(myControl.getCurrentMode()) {
    case PLAY:
      break;
    case PROGRAM:
      break;
    case PRESET:
      break;
    default:
      break;  
  }

}
