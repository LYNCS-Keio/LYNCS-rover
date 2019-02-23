#pragma once
#include "../include/Csearch.h"
class ArduinoControl
{
private:
	Csearch csearch_;
public:
	ArduinoControl(/* args */);
	~ArduinoControl();
	int Init();
	int Csearch1();
	void Csearch2();
};
