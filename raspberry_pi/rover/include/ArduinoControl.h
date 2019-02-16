#pragma once
#include "../include/Csearch.h"
class ArduinoControl
{
private:
	Csearch csearch_;
public:
	ArduinoControl(/* args */);
	~ArduinoControl();
	void Csearch1();
	void Csearch2();
};