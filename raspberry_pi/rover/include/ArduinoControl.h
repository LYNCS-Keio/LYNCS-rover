#pragma once
#include "../include/Csearch.h"
#include "../include/TransferValuesToArduino.h"
class ArduinoControl
{
  private:
	Csearch csearch_;
	TransferValuesToArduino transfer_;
  public:
	ArduinoControl(/* args */);
	~ArduinoControl();
	int Init();
<<<<<<< HEAD
	int Csearch1();
=======
	int Transfer(int angle, unsigned char order);
	void Csearch1();
>>>>>>> b707e51e5f00c81c1fe8cec9d4e225282493a592
	void Csearch2();
};
