#include "../include/Csearch.h"
#include "../include/CalculateCsearch.h"
#include "../include/TransferValuesToArduino.h"
#include "../include/ArduinoControl.h"
#include <iostream>
using namespace std;

int count = 0;

ArduinoControl::ArduinoControl(/* args */)
{
}

ArduinoControl::~ArduinoControl()
{
}

int ArduinoControl::Init()
{
	int ret_cs = csearch_.Init();
	int ret_ar = transfer_.Init();
	if (ret_cs < 0 || ret_ar < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int ArduinoControl::Transfer(int angle, unsigned char order)
{
	transfer_.Transfer(angle, order);
}
int ArduinoControl::Csearch1()
{
	int judgei;
	double xy[2];
	for (int i = 0; i < 4; i++)
	{
		judgei = csearch_.Search(118, 117, 122, 119, xy);
		if (judgei == 2 or judgei == 3)
		{
			transfer_.Transfer(0, 1);
			cout << "0"
				 << " "
				 << "1" << endl;
			break;
		}
		if (judgei == 0)
		{
			return 1;
			break;
			return 1;
		}
	}
}

void ArduinoControl::Csearch2()
{
	int judgei;
	char k = 0;
	double answer;
	double xy[2];
	for (int i = 0; i < 4; i++)
	{

		judgei = csearch_.Search(10, 0, 180, 140, xy);
		switch (judgei)
		{
		case 0:
			transfer_.Transfer(0, 2);
			cout << "0"
				 << " "
				 << "2" << endl;
			break;
		case 2:
			answer = ConvertCoordinateToAngle(xy) * 1000;
			transfer_.Transfer((int)answer, 4);
			cout << answer << " "
				 << "4" << endl;
			break;
		case 3:
			transfer_.Transfer(0, 3);
			cout << "0"
				 << " "
				 << "3" << endl;
			break;
		default:
			break;
		}
	}
}
