/*
 * main.c
 *
 *  Created on: 31 ���. 2015 �.
 *      Author: garik
 *	
 *
 *
 *	PD0...PD7 - ����������, �� vcc
 *	PC0 - ������, �� gnd
 *
 *	
 *
 *
 *	
 *
 *
 * ������� �����. 5 �����������
 *
 * 
 */

#include <avr/io.h>
#include <util/delay.h> 	// ���������� ���������� ��������
#include <avr/interrupt.h>	// ���������� ���������� ����������

#define T_POLL 100


int main(void) {

unsigned char upDown=1;     // �������� � �������� �����
unsigned char cylon=0;      // ���������� ����������� LED

	DDRD = 0xFF;         // ������������� ���� D � 0 �� 7 ��� ������
	DDRC &= ~(1 << DDC0);     // Clear the PC0 pin
							  //PC0 (INT0 pin) is now an input

	 /////*�������� ��� �������� ��������*//
	 TCCR0 = 0;
	 TCCR0 = (0<<WGM11)|(0<<WGM10);
	 TCNT0 = T_POLL;
	 TIFR = (1<<TOV0);
	 TIMSK |= (1<<TOIE0);
	 TCCR0 |= (1<<CS02)|(0<<CS01)|(1<<CS00);
	 ///////////////////////////////////////


void loop() {
  if(upDown==1){                // ���� ���� �����, ��
    cylon++;
    if(cylon>=7) upDown=0;      // ����� ��������� ���������� ����� LED, �� � ����. ����� ���� ����
  	}
  else {
    cylon--;
    if(cylon==0) upDown=1;      // ����� ��������� ���������� ����� LED, �� � ����. ����� ���� �����
    }
  PORTD = ~(1 << cylon);         //�����
  _delay_ms(133);                // ����� 133 �� (133*8 ~ 1000ms = 1s)
  }

sei();							//��������� ����������
while (1){						//����������� ����
	loop();
	}
}

ISR(TIMER0_OVF_vect)			//���������� ����������
{
   /*���������� �������� ��������*/
   TCNT0 = T_POLL;

   /*����� ������*/
	if (bit_is_clear(PINC,PC0)) // ���� ������ ������ (���������� � vcc, ���������� �� gnd)
		{
		PORTD = ~PORTD;
			 _delay_ms(25);
		PORTD = ~PORTD;
		}

}
