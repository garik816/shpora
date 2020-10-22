/*
 * main.c
 *
 *  Created on: 31 авг. 2015 г.
 *      Author: garik
 *	
 *
 *
 *	PD0...PD7 - светодиоды, на vcc
 *	PC0 - кнопка, на gnd
 *
 *	
 *
 *
 *	
 *
 *
 * Бегущий огонь. 5 светодиодов
 *
 * 
 */

#include <avr/io.h>
#include <util/delay.h> 	// подключаем библиотеку задержки
#include <avr/interrupt.h>	// подключаем библиотеку прерываний

#define T_POLL 100


int main(void) {

unsigned char upDown=1;     // начинаем с движения вверх
unsigned char cylon=0;      // определяет очередность LED

	DDRD = 0xFF;         // устанавливаем порт D с 0 по 7 как выхода
	DDRC &= ~(1 << DDC0);     // Clear the PC0 pin
							  //PC0 (INT0 pin) is now an input

	 /////*значение для счетного регистра*//
	 TCCR0 = 0;
	 TCCR0 = (0<<WGM11)|(0<<WGM10);
	 TCNT0 = T_POLL;
	 TIFR = (1<<TOV0);
	 TIMSK |= (1<<TOIE0);
	 TCCR0 |= (1<<CS02)|(0<<CS01)|(1<<CS00);
	 ///////////////////////////////////////


void loop() {
  if(upDown==1){                // если идем вверх, то
    cylon++;
    if(cylon>=7) upDown=0;      // когда достигнут наибольший номер LED, то в след. цикле идем вниз
  	}
  else {
    cylon--;
    if(cylon==0) upDown=1;      // когда достигнут наименьший номер LED, то в след. цикле идем вверх
    }
  PORTD = ~(1 << cylon);         //сдвиг
  _delay_ms(133);                // пауза 133 мс (133*8 ~ 1000ms = 1s)
  }

sei();							//разрешаем прерывания
while (1){						//бесконечный цикл
	loop();
	}
}

ISR(TIMER0_OVF_vect)			//обработчик прерывания
{
   /*перезапись счетного регистра*/
   TCNT0 = T_POLL;

   /*опрос кнопки*/
	if (bit_is_clear(PINC,PC0)) // если кнопка нажата (подключена к vcc, замыкается на gnd)
		{
		PORTD = ~PORTD;
			 _delay_ms(25);
		PORTD = ~PORTD;
		}

}
