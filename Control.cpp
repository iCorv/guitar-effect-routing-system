#include "Control.h"



void Control::initControl() {
	// Setup the button with an internal pull-up :
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
  	debouncer1.attach(BUTTON_1);
  	debouncer1.interval(m_bounceInterval); 
    debouncer2.attach(BUTTON_2);
  	debouncer2.interval(m_bounceInterval); 
    debouncer3.attach(BUTTON_3);
  	debouncer3.interval(m_bounceInterval); 
    debouncer4.attach(BUTTON_4);
  	debouncer4.interval(m_bounceInterval); 
    debouncer5.attach(BUTTON_5);
  	debouncer5.interval(m_bounceInterval);
  	debouncerTap.attach(TAP);
  	debouncerTap.interval(m_bounceInterval); 
  	debouncerBankUp.attach(BANK_UP);
  	debouncerBankUp.interval(m_bounceInterval);
  	debouncerBankDown.attach(BANK_DOWN);
  	debouncerBankDown.interval(m_bounceInterval);

  	// Setup the LEDs
  	pinMode(LED_1,OUTPUT);
  	pinMode(LED_2,OUTPUT);
  	pinMode(LED_3,OUTPUT);
  	pinMode(LED_4,OUTPUT);
  	pinMode(LED_5,OUTPUT);
}