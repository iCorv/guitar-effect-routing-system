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

  	// setup tap output
  	pinMode(TAP_OUT, OUTPUT);
  	digitalWrite(TAP_OUT, LOW);

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

void Control::presetMode() {
	if(m_prevMode != m_currMode) {
		m_Bank.reset();
		changePreset(0);
	}
	updateButtonStatus();
	presetModeButton();
}

void Control::presetModeButton() {
	if(m_debouncerBankDown.rose()) {
		bankDown();
	}
	if(m_debouncerBankUp.rose()) {
		bankUp();
	}
	if(m_debouncerTap.rose()) {
		//digitalWrite(TAP_OUT, HIGH);
		//delay(3);
		digitalWrite(TAP_OUT, HIGH);
		delay(40);
		digitalWrite(TAP_OUT, LOW);
	}
	if(m_debouncer1.rose()) {
		changePreset(0);
	}
	if(m_debouncer2.rose()) {
		changePreset(1);
	}
	if(m_debouncer3.rose()) {
		changePreset(2);
	}
	if(m_debouncer4.rose()) {
		changePreset(3);
	}
	if(m_debouncer5.rose()) {
		changePreset(4);
	}
}

void Control::progMode() {
	if(m_prevMode != m_currMode) {
		toggleRelay(resetRelayStatus.fxLoops);
		lightOut();
	}
}

void Control::changePreset(int t_value) {
  	m_Bank.setPresetNum(t_value);
  	loadCurrentPreset();
  	toggleLED(m_ledPins[t_value]);
}

void Control::loadCurrentPreset() {
	toggleRelay(m_Bank.getCurrentPreset().fxLoops);
}

void Control::playMode() {
	if(m_prevMode != m_currMode) {
		toggleRelay(playModeRelayStatus.fxLoops);
		lightOut();
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
		playModeRelayStatus.fxLoops[6] = !playModeRelayStatus.fxLoops[6];
	}
	if(m_debouncerBankUp.rose()) {
		playModeRelayStatus.fxLoops[7] = !playModeRelayStatus.fxLoops[7];
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
void Control::blinkLED(int t_time, int t_repeats, int numLED, boolean t_lowOrHigh) {
	for(int i = 0; i < t_repeats; i++) {
		if(t_lowOrHigh) {
			for(int j = 0; j < numLED; j++) {
				digitalWrite(m_ledPins[j],HIGH);
			}
			t_lowOrHigh = !t_lowOrHigh;
		}else{
			for(int j = 0; j < numLED; j++) {
				digitalWrite(m_ledPins[j],LOW);
			}
			t_lowOrHigh = !t_lowOrHigh;
		}
		delay(t_time);
	}
}

// switch off all leds then light up the one specified
void Control::toggleLED(int t_ledPin) {
	lightOut();
	digitalWrite(t_ledPin, HIGH);
}
// switch off all leds
void Control::lightOut() {
	for(int i = 0; i < 5; i++){
		digitalWrite(m_ledPins[i], LOW);
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
	blinkLED(100,9, 5, false);
}


void Control::changeBank(int t_value) {
	m_Bank.setBankNum(t_value);
	loadCurrentPreset();
	blinkLED(100, 9, t_value+1, true);
  	toggleLED(LED_1);
}

void Control::bankUp() {
	int t_currBank = m_Bank.getCurrentBank();
	// wrap to first bank if we already reached the last bank 
	if(t_currBank == 4) {
		changeBank(0);
	}else{
		changeBank(t_currBank+1);
	}
}

void Control::bankDown() {
	int t_currBank = m_Bank.getCurrentBank();
	// wrap to last bank if we already reached the first bank 
	if(t_currBank == 0) {
		changeBank(4);
	}else{
		changeBank(t_currBank-1);
	}
}