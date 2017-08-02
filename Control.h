#pragma once
#include <Arduino.h>
#include <Bounce2.h>

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

enum Modus { PLAY, PRESET, PROGRAM };

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
		m_currMode(PRESET)
	{

	}
	void initControl();
	boolean switchListener();
	Modus getCurrentMode();
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
	const int m_bounceInterval{ 5 }; // cool-down time of buttons in ms
	const int m_relayPins[10] = {25,24,23,22,21,20,19,18,38,39}; // pins of relay modules
	const int m_numRelays{ 10 }; // number of relays
	void startJingle();
	void blinkLED(int t_time, int t_repeats, boolean t_lowOrHigh);
	Modus m_currMode;
};



