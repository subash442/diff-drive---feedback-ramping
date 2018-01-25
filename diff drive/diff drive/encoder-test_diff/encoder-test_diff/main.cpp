/*
 * encoder-test_diff.cpp
 *
 * Created: 12/5/2017 12:25:14 PM
 * Author : Ab Timilsina
 */ 
 #ifndef F_CPU
 #define F_CPU	16000000UL
 #endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motor.h"
#include "Encoder.h"
#include "uart.h"

 Encoder e[2];

int main(void)
{
  Motor m1,m2;
  m1.Initialise(1),m2.Initialise(2);
   e[0].Initialise(1),e[1].Initialise(2);
   initUART0();
   m1.SetOcrValue(249);
  m2.SetOcrValue(249);
     sei();
    while (1) 
    {
		//UART0TransmitString("E1: ");
		//UART0TransmitData(e[0].Get_count());
		//UART0Transmit('\t');
//
		//UART0TransmitString("E2: ");
		//UART0TransmitData(e[1].Get_count());
		//UART0Transmit('\n');
    }
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
	e[1].Calc_Speed();
	UART0TransmitData(e[1].Get_Speed());
	UART0Transmit('\n');
}
