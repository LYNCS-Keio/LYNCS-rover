#include "../include/Csearch.h"
#include "../include/CalculateCsearch.h"
#include "../include/TransferValuesToArduino.h"
#include "../include/ArduinoControl.h"
#include <iomanip> //時間を取得
#include <sstream> //値を文字列にする
using namespace std;

int count = 0;

ArduinoControl::ArduinoControl(/* args */) : log_file_("rover.log")
{
}

ArduinoControl::~ArduinoControl()
{
}

int ArduinoControl::Init()
{
	log_file_ << "start" << endl;
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
	time_t t = time(nullptr);
	const tm *lt = localtime(&t);
	std::stringstream s;
	s << "20";
	s << lt->tm_year - 100; //100を引くことで20xxのxxの部分になる
	s << "-";
	s << lt->tm_mon + 1; //月を0からカウントしているため
	s << "-";
	s << lt->tm_mday; //そのまま
	s<< "-";
	s<< lt->tm_hour;
	s<< "-";
	s<< lt->tm_min;
	s<< "-";
	s<< lt->tm_sec;
	//result = "2015-5-19-11-30-21"
	std::string result = s.str();
	log_file_ << result << endl;
}
int ArduinoControl::Csearch1()
{
	int judgei;
	char k = 0;
	double xy[2];

	while (k < 4)
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

		k++;
	}
}

void ArduinoControl::Csearch2()
{
	int judgei;
	char k = 0;
	double answer;
	double xy[2];

	while (k < 4)
	{
		judgei = csearch_.Search(10, 0, 180, 140, xy);
		if (judgei == 2)
		{
			answer = ConvertCoordinateToAngle(xy) * 1000;
			transfer_.Transfer((int)answer, 4);
			cout << answer << " "
				 << "4" << endl;
			break;
		}
		if (judgei == 0)
		{
			transfer_.Transfer(0, 2);
			cout << "0"
				 << " "
				 << "2" << endl;
			break;
		}
		if (judgei == 3)
		{
			transfer_.Transfer(0, 3);
			cout << "0"
				 << " "
				 << "3" << endl;
			break;
		}

		k++;
	}
}
