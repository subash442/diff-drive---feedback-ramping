/* 
* Robodrive.h
*
* Created: 12/3/2017 8:50:34 PM
* Author: Subash Timilsina
*/


#ifndef __ROBODRIVE_H__
#define __ROBODRIVE_H__

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

#include "Motor.h"
#include "PID.h"
#include "Encoder.h"
#include "uart.h"

#define MAX_ROBVEL				240.0		//in RPM
#define CIRCUMFERENCE_DISTANCE	452.0			//in mm //diameter of wheel 144mm
#define RAMP_STEP				0.1


class Robodrive
{
	private:
		int robovelocity[2];
		int wheel_velocity[2];
		int motor_val[2];
		float sp[2];
		bool dir;

		Motor m[2];
		PID p[2];

		int robovel;
		long int destination;
		long int calc_distcount;
		long int enc_distance;
	public:
		void Initialize_robot();
		void Get_Joystick_Data(char dat);
		void Calc_velocity();
		void Update_velocity();	
		void reset_robotvelocity();                                                                                
		void perform_ramping();
}; 

#endif //__ROBODRIVE_H__
