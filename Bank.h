#pragma once
#include <Arduino.h>
#include <EEPROM.h>

struct preset {
	boolean fxLoops[10] = {false,false,false,false,false,false,false,false,false,false};
};

class Bank
{
public:
	Bank()
		: m_currBankNum(0),
		  m_currPresetNum(0)
	{
		loadBank();
		printPreset(m_currPresetNum);
	}
	preset* BankUp();
	preset* BankDown();
	preset* getCurrentBank();
	preset getCurrentPreset();
  	void setLoop(int t_loopNum, boolean t_status);
  	void savePreset();
  	void printPreset(int t_numPreset);
private:
	const uint8_t m_numBanks{ 5 }; // change if more presets are needed
	const uint8_t m_numPresets{ 5 }; // number of presets per Bank
	const uint8_t m_numLoops{ 10 }; // number of fx loops per preset
	const uint8_t m_numLoopsPerPreset{ m_numPresets*m_numLoops }; // number of fx loops per bank
	uint8_t m_currBankNum;
	uint8_t m_currPresetNum;
	struct preset m_currPresets[5];
  	struct preset m_tempPreset;
	void loadPreset(int t_numBank);
	void loadBank();
};
