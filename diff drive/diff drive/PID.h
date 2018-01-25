/* 
* PID.h
*
* Created: 10/28/2017 11:53:41 AM
* Author: Subash Timilsina
*/


#ifndef __PID_H__
#define __PID_H__

#include <avr/io.h>
#include <math.h>

class PID
{
	private:
		float kp,ki,kd;
		int sp; 
		int error , lastinput , errorsum;
		int cv ;
		int iterm, dterm, pterm ;
	public: 
		PID():kp(0),ki(0),kd(0),sp(0),error(0),lastinput(0),errorsum(0),cv(0){};
		void Set_P(float kP){kp = kP;};
		void Set_I(float kI){ki = kI;};
		void Set_D(float kD){kd = kD;};	
		void Set_SP(int sP){sp=sP;};
		int  Get_SP(){return sp;};
		void Inc_P(){kp+=0.005;};
		void Inc_I(){ki+=0.001;};
		void Inc_D(){kd+=0.01;};
		void Dcr_P(){kp-=0.005;};
		void Dcr_I(){ki-=0.001;};
		void Dcr_D(){kd-=0.01;};
		void Set_Pid(float kP,float kI,float kD);
		float Get_P();
		float Get_I();
		float Get_D();
		int Compute(int input);
		void limit_values(int &term,int min,int max);

}; 

#endif //__PID_H__
