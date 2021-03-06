#include "Bank.h"

preset Bank::getCurrentPreset() {
	return m_currPresets[m_currPresetNum];
}

int Bank::getCurrentBank() {
	return m_currBankNum;
}

void Bank::loadBank() {
	for(int i = 0; i < m_numPresets; i++) {
		loadPreset(i);
	}
}

void Bank::loadPreset(int t_numPreset) {
	int offset = t_numPreset*m_numLoops+m_currBankNum*m_numLoopsPerPreset;
	for(int j = 0; j < m_numLoops; j++) {
		m_currPresets[t_numPreset].fxLoops[j] = EEPROM.read(j+offset);
	}
}

void Bank::savePreset() {
	int offset = m_currPresetNum*m_numLoops+m_currBankNum*m_numLoopsPerPreset;
	for(int j = 0; j < m_numLoops; j++) {
		// EEPROM.put uses EEPROM.update. Data will only be written if it is different from Data already saved.
		// Since we only save boolean it is highly likely we dont need to write!
		// This increases the lifetime of eeprom.
		EEPROM.put(j+offset, m_tempPreset.fxLoops[j]);
	}
	loadPreset(m_currPresetNum);
}

void Bank::setLoop(int t_loopNum, boolean t_status) {
 	m_tempPreset.fxLoops[t_loopNum] = t_status;
}

void Bank::setPresetNum(int t_value) {
  	m_currPresetNum = t_value;
  	loadPreset(m_currPresetNum);
}

void Bank::setBankNum(int t_value) {
	m_currPresetNum = 0;
  	m_currBankNum = t_value;
  	loadBank();
}

void Bank::reset() {
	m_currPresetNum = 0;
	m_currBankNum = 0;
	loadBank();
}

void Bank::printPreset(int t_numPreset) {
	for(int j = 0; j < m_numLoops; j++) {
		Serial.println(m_currPresets[t_numPreset].fxLoops[j]);
	}
}
