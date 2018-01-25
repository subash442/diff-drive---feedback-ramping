/*
 * diff drive.cpp
 *
 * Created: 11/17/2017 5:55:45 PM
 * Author : Subash Timilsina
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Robodrive.h"	


int main(void)
{
	sei();
	char ch;
	initUART0();
	initUART3();
	Robodrive Diff_Drive;
	Diff_Drive.Initialize_robot();
    while (1) 
    {
		ch = '0';
		ch = UART3Receive();
		Diff_Drive.Get_Joystick_Data(ch);
		Diff_Drive.Calc_velocity();
		Diff_Drive.Update_velocity();	
    }
}


