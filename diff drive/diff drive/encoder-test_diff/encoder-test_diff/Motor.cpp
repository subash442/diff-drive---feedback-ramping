#include "Motor.h"



void Motor::Initialise(uint8_t no)
{
	num = no;
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor::InitPWM()
{
	if (num==1)
	{
		OUTPUT(DD_F1);
		OUTPUT(DD_B1);

		OUTPUT(DD_PWM1);

		PWM_TCCRA1	|=  ( 1 << PWM_1COM1 ) | ( 1 << PWM_1WGM1 );														//
		PWM_TCCRB1	|=  ( 1 << PWM_1WGM2 ) | ( 1 << PWM_1WGM3 ) | ( 1 << PWM_1CS1);									//PRESCALAR 8
		PWM_ICR1		 =         ICR_TOP;
	}
	else if(num==2)
	{
		OUTPUT(DD_F2);
		OUTPUT(DD_B2);

		OUTPUT(DD_PWM2);

		PWM_TCCRA2	|=  ( 1 << PWM_2COM1 ) | ( 1 << PWM_2WGM1 );														//
		PWM_TCCRB2	|=  ( 1 << PWM_2WGM2 ) | ( 1 << PWM_2WGM3 ) | ( 1 << PWM_2CS1);									//PRESCALAR 8
		PWM_ICR2		 =         ICR_TOP;
	}
	
}

void Motor::SetForwardDirection()
{
	switch(num)
	{
		case 1:
			SET		(DD_F1);
			CLEAR	(DD_B1);
			break;
		case 2:
			SET		(DD_F2);
			CLEAR	(DD_B2);
			break;
		
	}
	

}
void Motor::SetReverseDirection()
{
	switch(num)
	{
		case 1:
			CLEAR	(DD_F1);
			SET		(DD_B1);
			break;
		case 2:
			CLEAR	(DD_F2);
			SET		(DD_B2);
			break;
	}

}

void Motor::StopMotor()
{
	switch(num)
	{
		case 1:
			CLEAR	(DD_F1);
			CLEAR	(DD_B1);

			PWM_OCR1 = 0;
			break;
		case 2:
			CLEAR	(DD_F2);
			CLEAR	(DD_B2);

			PWM_OCR2 = 0;
			break;
	}
}


void Motor::SetOcrValue(int Ocr)
{
	if (Ocr > 0)
		SetForwardDirection();
	if( Ocr < 0)
	{
		Ocr = -Ocr;
		SetReverseDirection();
	}
	if( Ocr >= MAX_VALUE)
		Ocr = MAX_VALUE;

	switch(num)
	{
		case 1:
			PWM_OCR1	= Ocr;
			break;
		case 2:
			PWM_OCR2	= Ocr;
			break;
	}
}
