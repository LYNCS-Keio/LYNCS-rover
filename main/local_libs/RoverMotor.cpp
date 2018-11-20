#include <Arduino.h>
#include "RoverMotor.h"
namespace lyncs
{

RoverMotor::RoverMotor()
	: kOutR1_(5),
	  kOutR2_(6),
	  kOutL1_(9),
	  kOutL2_(10)
{
}

RoverMotor::~RoverMotor()
{
}
RoverMotor::Init()
{
	pinMode(kOutR1_, OUTPUT);
	pinMode(kOutR2_, OUTPUT);
	pinMode(kOutL1_, OUTPUT);
	pinMode(kOutL2_, OUTPUT);
}
void RoverMotor::RoverOutput(uint8_t outR,uint8_t outL){
    digitalWrite(kOutR1_, LOW);
    analogWrite(kOutR2_, outR);wsqgcdjo
}
} // namespace lyncs