#include "Control.h"


void Control::initControl() {
	// Setup the buttons with an internal pull-up :
  	pinMode(BUTTON_1, INPUT_PULLUP);
  	pinMode(BUTTON_2, INPUT_PULLUP);
  	pinMode(BUTTON_3, INPUT_PULLUP);
  	pinMode(BUTTON_4, INPUT_PULLUP);
  	pinMode(BUTTON_5, INPUT_PULLUP);
  	pinMode(TAP, INPUT_PULLUP);
	pinMode(BANK_DOWN, INPUT_PULLUP);
	pinMode(BANK_UP, INPUT_PULLUP);
	pinMode(SWITCH_2, INPUT_PULLUP);
	pinMode(SWITCH_1, INPUT_PULLUP);

	// After setting up the button, setup the Bounce instance
  	m_debouncer1.attach(BUTTON_1);
  	m_debouncer1.interval(m_bounceInterval); 
    m_debouncer2.attach(BUTTON_2);
  	m_debouncer2.interval(m_bounceInterval); 
    m_debouncer3.attach(BUTTON_3);
  	m_debouncer3.interval(m_bounceInterval); 
    m_debouncer4.attach(BUTTON_4);
  	m_debouncer4.interval(m_bounceInterval); 
    m_debouncer5.attach(BUTTON_5);
  	m_debouncer5.interval(m_bounceInterval);
  	m_debouncerTap.attach(TAP);
  	m_debouncerTap.interval(m_bounceInterval); 
  	m_debouncerBankUp.attach(BANK_UP);
  	m_debouncerBankUp.interval(m_bounceInterval);
  	m_debouncerBankDown.attach(BANK_DOWN);
  	m_debouncerBankDown.interval(m_bounceInterval);

  	// Setup the LEDs
  	pinMode(LED_1,OUTPUT);
  	pinMode(LED_2,OUTPUT);
  	pinMode(LED_3,OUTPUT);
  	pinMode(LED_4,OUTPUT);
  	pinMode(LED_5,OUTPUT);

  	// Setup relay pins
  	for(int i = 0; i < m_numRelays; i++) {
  		pinMode(m_relayPins[i], OUTPUT);
  		digitalWrite(m_relayPins[i], LOW);
  	}


  	startJingle();
}


boolean Control::switchListener() {
	if(digitalRead(SWITCH_1) == HIGH) {
		m_prevMode = m_currMode;
		m_currMode = PLAY;
		//Serial.println("Play Mode!");
		return true;
	}
	if(digitalRead(SWITCH_2) == HIGH) {
		m_prevMode = m_currMode;
		m_currMode = PROGRAM;
		//Serial.println("Program Mode!");
		return true;
	}else{
		m_prevMode = m_currMode;
		m_currMode = PRESET;
		return true;
	}
}

void Control::toggleRelay(boolean *t_relayStatus) {
	for(int i = 0; i < m_numRelays; i++) {
		if(t_relayStatus[i] != currRelayStatus.fxLoops[i]) {
			digitalWrite(m_relayPins[i], HIGH);
			currRelayStatus.fxLoops[i] = !currRelayStatus.fxLoops[i];
		}
	}
	delay(8);
	for(int i = 0; i < m_numRelays; i++) {
		digitalWrite(m_relayPins[i], LOW);
	}
}

void Control::progMode() {
	if(m_prevMode != m_currMode) {
		toggleRelay(resetRelayStatus.fxLoops);
	}
}

void Control::loadCurrentPreset() {
	preset currPreset = m_Bank.getCurrentPreset();
	toggleRelay(currPreset.fxLoops);
}

void Control::playMode() {
	if(m_prevMode != m_currMode) {
		toggleRelay(playModeRelayStatus.fxLoops);
	}
	updateButtonStatus();
	playModeButton();
	toggleRelay(playModeRelayStatus.fxLoops);
}

Modus Control::getCurrentMode() {
	return m_currMode;
}

void Control::updateButtonStatus() {
	m_debouncer1.update(); 
	m_debouncer2.update(); 
	m_debouncer3.update(); 
	m_debouncer4.update(); 
	m_debouncer5.update();
	m_debouncerTap.update();
	m_debouncerBankUp.update();
	m_debouncerBankDown.update();
}

void Control::playModeButton() {
	if(m_debouncerBankDown.rose()) {
		playModeRelayStatus.fxLoops[7] = !playModeRelayStatus.fxLoops[7];
	}
	if(m_debouncerBankUp.rose()) {
		playModeRelayStatus.fxLoops[6] = !playModeRelayStatus.fxLoops[6];
	}
	if(m_debouncerTap.rose()) {
		playModeRelayStatus.fxLoops[5] = !playModeRelayStatus.fxLoops[5];
	}
	if(m_debouncer1.rose()) {
		playModeRelayStatus.fxLoops[4] = !playModeRelayStatus.fxLoops[4];
	}
	if(m_debouncer2.rose()) {
		playModeRelayStatus.fxLoops[3] = !playModeRelayStatus.fxLoops[3];
	}
	if(m_debouncer3.rose()) {
		playModeRelayStatus.fxLoops[2] = !playModeRelayStatus.fxLoops[2];
	}
	if(m_debouncer4.rose()) {
		playModeRelayStatus.fxLoops[1] = !playModeRelayStatus.fxLoops[1];
	}
	if(m_debouncer5.rose()) {
		playModeRelayStatus.fxLoops[0] = !playModeRelayStatus.fxLoops[0];
	}
}

void Control::setLoop(int t_loopNum, boolean t_status) {
	m_Bank.setLoop(t_loopNum,t_status);
}

void Control::savePreset() {
	m_Bank.savePreset();
}

// t_lowOrHigh = true - starts with LED on, else with LED off
// this function uses delay therefore blocks all
void Control::blinkLED(int t_time, int t_repeats, boolean t_lowOrHigh) {
	for(int i = 0; i < t_repeats; i++) {
		if(t_lowOrHigh) {
			digitalWrite(LED_5, HIGH);
			digitalWrite(LED_4, HIGH);
			digitalWrite(LED_3, HIGH);
			digitalWrite(LED_2, HIGH);
			digitalWrite(LED_1, HIGH);
			t_lowOrHigh = !t_lowOrHigh;
		}else{
			digitalWrite(LED_5, LOW);
			digitalWrite(LED_4, LOW);
			digitalWrite(LED_3, LOW);
			digitalWrite(LED_2, LOW);
			digitalWrite(LED_1, LOW);
			t_lowOrHigh = !t_lowOrHigh;
		}
		delay(t_time);
	}
}

void Control::startJingle() {
	digitalWrite(LED_1, HIGH);
	delay(300);
	digitalWrite(LED_2, HIGH);
	delay(300);
	digitalWrite(LED_3, HIGH);
	delay(300);
	digitalWrite(LED_4, HIGH);
	delay(300);
	digitalWrite(LED_5, HIGH);
	delay(300);
	// blink two times
	blinkLED(100,9,false);
}
