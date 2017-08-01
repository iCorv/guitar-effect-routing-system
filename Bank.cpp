#include "Bank.h"



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
		EEPROM.write(j+offset, m_tempPreset.fxLoops[j]);
	}
	loadPreset(m_currPresetNum);
}

void Bank::setLoop(int t_loopNum, boolean t_status) {
 	m_tempPreset.fxLoops[t_loopNum] = t_status;
}

void Bank::printPreset(int t_numPreset) {
	for(int j = 0; j < m_numLoops; j++) {
		Serial.println(m_currPresets[t_numPreset].fxLoops[j]);
	}
}