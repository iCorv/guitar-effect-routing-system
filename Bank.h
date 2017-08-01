#pragma once

struct preset {
	bool loops[10];
}

class Bank
{
public:
	Bank()
		: m_currBank(1)
	{

	}
	bool BankUp();
	bool BankDown();
private:
	const int m_numPresets{ 5 }; // change if more presets are needed
	int m_currBank;
	void loadPreset();
};