#include <ArdOSCForSerial.h>
#include "Control.h"

unsigned long networkTimeoutMillis = 3;      // How long to wait for an UDP-Package to finish. Play with this value if you loose messages
Control myControl;
OSCServer server(&Serial, networkTimeoutMillis);   // the OSC Server will get it's data from the Serial passed to it.

void setup() {
  Serial.begin(115200);

  myControl.initControl();
  server.addCallback("/ard/fxloops", &setFxLoops);
  server.addCallback("/ard/save", &saveFxLoops);
  server.addCallback("/ard/preset", &setPresetNum);
  server.addCallback("/ard/bank", &setBankNum);
}

void loop() {
  // check if switch has changed
  myControl.switchListener();

  switch(myControl.getCurrentMode()) {
    case PLAY:
      myControl.playMode();
      // keep serial clean so no stray msg are left when going to progMode
      Serial.flush();
      break;
    case PROGRAM:
      // If a message with a registered adress is received, the Server will callback function (in this case setLedFade()) will be invoked.
      server.availableCheck(); //check for new incoming messages.
      myControl.progMode();
      break;
    case PRESET:
    myControl.presetMode();
      // keep serial clean so no stray msg are left when going to progMode
      Serial.flush();
      break;
    default:
      break;  
  }

}

void setPresetNum(OSCMessage *t_mes) {
  int presetNum = t_mes->getArgInt32(0);
  myControl.changePreset(presetNum);
}

void setBankNum(OSCMessage *t_mes) {
  int bankNum = t_mes->getArgInt32(0);
  myControl.changeBank(bankNum);
}

void saveFxLoops(OSCMessage *t_mes) {
  myControl.savePreset();
  myControl.loadCurrentPreset();
  myControl.startJingle();
}

void setFxLoops(OSCMessage *t_mes) {
  for(int i = 0; i < 10; i++) {
    float loopStatus = t_mes->getArgFloat(i);
    if(loopStatus == 1.0) {
      myControl.setLoop(9-i, true);
    }else{
      myControl.setLoop(9-i, false);
    }
  }
}
