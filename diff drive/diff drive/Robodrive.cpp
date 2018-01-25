/* 
* Robodrive.cpp
*
* Created: 12/3/2017 8:50:34 PM
* Author: Subash Timilsina
*/


#include "Robodrive.h"

volatile bool pidflag = false;
Encoder e[2];

void Robodrive::Initialize_robot()
{
	for(int i = 0;i<2;i++)               
	{
		sp[i] = 0;
		m[i].Initialise(i+1);
		e[i].Initialise(i+1);
		p[i].Set_Pid(2.45,0,7.35); //2.074 ,0 , 9.5    // for robvel = 80	pid = 1.364 0 6.26 //for robvel = 240 pid = 1.619 0 9.16
	}
	calc_distcount = 0;
	enc_distance = 0;
	robovel = 240;
	dir = true;
	reset_robotvelocity();
}

void Robodrive::Get_Joystick_Data(char dat)
{
	
	
	switch(dat)
	{
		case 'f':
		{
			robovelocity[0] = robovel;
			robovelocity[1] = 0;
			destination = 3900;
			calc_distcount = ((destination/CIRCUMFERENCE_DISTANCE)*PPR);
			enc_distance = 0;
			dir = true;
			break;
		}
		case 'b':
		{
			robovelocity[0] = -robovel;
			robovelocity[1] = 0;
			destination = 3900;
			calc_distcount = ((destination/CIRCUMFERENCE_DISTANCE)*PPR);
			enc_distance = 0;
			dir = false;
			break;
		}
		case 's':
		{
			reset_robotvelocity();
			break;
		}
		default: break;
	}
}

void Robodrive::Calc_velocity()
{
	wheel_velocity[0] = (robovelocity[0]+robovelocity[1]);
	wheel_velocity[1] = (robovelocity[0]-robovelocity[1]);
	motor_val[0]=(PPR*wheel_velocity[0])/3000.0;
	motor_val[1]=(PPR*wheel_velocity[1])/3000.0;
	p[0].Set_SP(sp[0]);//motor_val[0]);//motor_val[0]);		//	250/225	= 1.11	PPR/MAX_ROBVEL
	p[1].Set_SP(sp[1]);//motor_val[1]);//motor_val[1]);		//	250/225	= 1.11	PPR/MAX_ROBVEL


}


void Robodrive::Update_velocity()
{
	if(pidflag)
	{
		enc_distance += e[0].Get_Speed();
		m[0].SetOcrValue(p[0].Compute(e[0].Get_Speed()));
		m[1].SetOcrValue(p[1].Compute(e[1].Get_Speed()));
		pidflag = false;
	} 
	perform_ramping();

	//UART0TransmitData(25);
	//UART0Transmit(' ');
	//UART0TransmitData(-25);
	//UART0Transmit(' ');
	//UART0TransmitData(p[0].Get_SP());
	//UART0Transmit(' ');
	//UART0TransmitData(e[0].Get_Speed());
	//UART0Transmit(' ');
	//UART0TransmitData(e[1].Get_Speed());
	//UART0Transmit('\n');

}

void Robodrive::perform_ramping()
{
	if (abs(enc_distance) <= int(0.2*(calc_distcount)))
	{
		//ramp up
		if (dir)
		{
			sp[0] += RAMP_STEP;
			sp[1] += RAMP_STEP;
		}
		else 
		{
			sp[0] -= RAMP_STEP;
			sp[1] -= RAMP_STEP;
		}
		
	}
	else if ((abs(enc_distance) >= int(0.7*calc_distcount))&&(abs(enc_distance) <= int(calc_distcount)))
	{
		//ramp down
		if (dir)
		{
			sp[0] -= RAMP_STEP;
			sp[1] -= RAMP_STEP;
		}
		else
		{
			sp[0] += RAMP_STEP;
			sp[1] += RAMP_STEP;
		}
	}
	else if ((abs(enc_distance) >= int(0.2*calc_distcount))&&(abs(enc_distance) <= int(0.7*calc_distcount)))
	{
		sp[0] = motor_val[0];
		sp[1] = motor_val[1];
	}
	else if (abs(enc_distance) >= int(calc_distcount))
	{
		//stop
		sp[0] = 0;
		sp[1] = 0;
		reset_robotvelocity();
	}
	UART0TransmitData(calc_distcount);
	UART0Transmit('\t');
	UART0TransmitData(abs(enc_distance));
	UART0Transmit('\t');
	UART0TransmitData(sp[0]);
	UART0Transmit('\t');
	UART0TransmitData(sp[1]);
	UART0Transmit('\n');
}

void Robodrive::reset_robotvelocity()
{
	robovelocity[0] = 0;
	robovelocity[1] = 0;
}


ISR(INT_VECT1)
{
	if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
		e[0].incCount();
	}
	else
	e[0].dcrCount();

}

ISR(INT_VECT2)
{
	if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
		e[1].incCount();
	}
	else
	e[1].dcrCount();
}

ISR(TIMER5_COMPA_vect)
{
	e[0].Calc_Speed();
	e[1].Calc_Speed();
	pidflag = true;
}