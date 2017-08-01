#include "Bank.h"
#include "Control.h"

preset m_currPreset;

Bank myBank;
Control myControl;

void setup() {
  Serial.begin(115200);
  //myBank.setLoop(7,true);
  //myBank.savePreset();
  myBank.printPreset(1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
