#pragma once
#include <Arduino.h>
#include <Bounce2.h>
#include <ArdOSCForSerial.h>
#include "Bank.h"

// button and switch pins
#define BUTTON_5 8
#define BUTTON_4 9
#define BUTTON_3 10
#define BUTTON_2 11
#define BUTTON_1 12
#define TAP 13
#define BANK_DOWN 14
#define BANK_UP 15
#define SWITCH_1 16
#define SWITCH_2 17
// led pins
#define LED_5 41
#define LED_4 42
#define LED_3 43
#define LED_2 44
#define LED_1 45
// tap output
#define TAP_OUT 40

enum Modus { PLAY, PRESET, PROGRAM, START, OFF };

class Control
{
public:
	Control()
		: m_debouncer1(Bounce()),
		m_debouncer2(Bounce()),
		m_debouncer3(Bounce()),
		m_debouncer4(Bounce()),
		m_debouncer5(Bounce()),
		m_debouncerTap(Bounce()),
		m_debouncerBankUp(Bounce()),
		m_debouncerBankDown(Bounce()),
		m_currMode(START),
		m_prevMode(OFF),
		m_Bank(Bank())
	{
		for(int i = 8; i < m_numRelays; i++) {
			playModeRelayStatus.fxLoops[i] = true;
		}
	}
	void initControl();
	void startJingle();
	boolean switchListener();
	Modus getCurrentMode();
	void playMode();
	void progMode();
	void presetMode();
	void loadCurrentPreset() ;
	void setLoop(int t_loopNum, boolean t_status);
	void savePreset();
  	void changePreset(int t_value);
  	void changeBank(int t_value);
private:
	// Instantiate Bounce objects
	Bounce m_debouncer1; 
	Bounce m_debouncer2; 
	Bounce m_debouncer3; 
	Bounce m_debouncer4; 
	Bounce m_debouncer5;
	Bounce m_debouncerTap;
	Bounce m_debouncerBankUp;
	Bounce m_debouncerBankDown;
	const uint8_t m_bounceInterval{ 5 }; // cool-down time of buttons in ms
	const uint8_t m_relayPins[10] = {25,24,23,22,21,20,18,19,39,38}; // pins of relay modules
	const uint8_t m_numRelays{ 10 }; // number of relays
	const uint8_t m_ledPins[5] = {LED_1, LED_2, LED_3, LED_4, LED_5};

	void toggleRelay(boolean *t_relayNum);
	void blinkLED(int t_time, int t_repeats, int numLED, boolean t_lowOrHigh);
	void updateButtonStatus();
	void playModeButton();
	void presetModeButton();
	void toggleLED(int t_ledPin);
	void lightOut();
	void bankUp();
	void bankDown();
	Modus m_currMode;
	Modus m_prevMode;

	Bank m_Bank;
	preset playModeRelayStatus;
	preset currRelayStatus;
	preset resetRelayStatus;
};



