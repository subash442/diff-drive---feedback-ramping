/* 
* PID.cpp
*
* Created: 10/28/2017 11:53:40 AM
* Author: Subash Timilsina
*/


#include "PID.h"

void PID::Set_Pid(float kP,float kI,float kD)
{
	kp = kP;
	ki = kI;
	kd = kD;	
}

float PID::Get_P()
{
	return kp;
}

float PID::Get_I()
{
	return ki;
}

float PID::Get_D()
{
	return kd;
}

int PID::Compute(int input)
{
	error = sp - input;
	
	//pterm calculation
	
	pterm = error*kp;
	
	//iterm calculation
	 
	 errorsum += error;
	 iterm = errorsum*ki;
	 limit_values(iterm,-165,165);
	 
	 //dterm calculation
	 
	 dterm = kd*(input-lastinput);         
	
	lastinput = input;
	
	
	if (fabs(error)>1)//error tolerance
	{
		cv += pterm + iterm - dterm;
	}
	
	return cv;
}


void PID::limit_values(int &term,int min,int max)
{
	if (term >  max) term = max;
	if (term < min) term = min;
}
	