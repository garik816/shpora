/*
 * main.c
 *
 *  Created on: 18 ����. 2016
 *      Author: garik
 *
 *
 *
 *
 *
 *      to do list:
 *
 *      - ����������� �������� �������� ������� alarm()
 *      -
 *
 *
 *
 *
 *
 *
 */

#include <avr/io.h>
#include <util/delay.h> 	// ���������� ���������� ��������
#include <avr/interrupt.h>	// ���������� ���������� ����������
#include <stdlib.h>




int main(void){

	DDRC	= 0b00000001;
	PORTC	= 0b00101110;



	 /////*�������� ��� �������� ��������*//
	 TCCR0 = 0;
	 TCCR0 = (0<<WGM11)|(0<<WGM10);
	 TCNT0 = 100;
	 TIFR = (1<<TOV0);
	 TIMSK |= (1<<TOIE0);
	 TCCR0 |= (1<<CS02)|(0<<CS01)|(1<<CS00);
	 ///////////////////////////////////////


void loop() {



  }

sei();							//��������� ����������
while (1){						//����������� ����
	loop();
	}
}





ISR(TIMER0_OVF_vect)			//���������� ����������
{
   /*���������� �������� ��������*/
   TCNT0 = 100;

   	/*����� ������� �1*/
	if (bit_is_set(PINC,PC1)) // ���� ������ ������ (���������� � gnd, ���������� �� vcc)
		{
		PORTC |= (1<<0);		//alarm on
		}

	/*����� ������� �2*/
	else if (bit_is_set(PINC,PC2)) // ���� ������ ������ (���������� � gnd, ���������� �� vcc)
		{
		PORTC |= (1<<0);		//alarm on
		}

	/*����� vibro*/
	else if (bit_is_set(PINC,PC3)) // ���� ������ ������ (���������� � gnd, ���������� �� vcc)
		{
		PORTC |= (1<<0);		//alarm on
		}

	/*����� ������ ������*/
	else if (bit_is_set(PINC,PC5)) // ���� ������ ������ (���������� � gnd, ���������� �� vcc)
		{
		PORTC &= (~(1<<0));		//alarm off
		}
}
