/*
 * main.c
 *
 *  Created on: 18 февр. 2016
 *      Author: garik
 *
 *
 *
 *
 *
 *      to do list:
 *
 *      - обработчики датчиков вызывают функцию alarm()
 *      -
 *
 *
 *
 *
 *
 *
 */

#include <avr/io.h>
#include <util/delay.h> 	// подключаем библиотеку задержки
#include <avr/interrupt.h>	// подключаем библиотеку прерываний
#include <stdlib.h>




int main(void){

	DDRC	= 0b00000001;
	PORTC	= 0b00101110;



	 /////*значение для счетного регистра*//
	 TCCR0 = 0;
	 TCCR0 = (0<<WGM11)|(0<<WGM10);
	 TCNT0 = 100;
	 TIFR = (1<<TOV0);
	 TIMSK |= (1<<TOIE0);
	 TCCR0 |= (1<<CS02)|(0<<CS01)|(1<<CS00);
	 ///////////////////////////////////////


void loop() {



  }

sei();							//разрешаем прерывания
while (1){						//бесконечный цикл
	loop();
	}
}





ISR(TIMER0_OVF_vect)			//обработчик прерывания
{
   /*перезапись счетного регистра*/
   TCNT0 = 100;

   	/*опрос геркона №1*/
	if (bit_is_set(PINC,PC1)) // если кнопка нажата (подключена к gnd, замыкается на vcc)
		{
		PORTC |= (1<<0);		//alarm on
		}

	/*опрос геркона №2*/
	else if (bit_is_set(PINC,PC2)) // если кнопка нажата (подключена к gnd, замыкается на vcc)
		{
		PORTC |= (1<<0);		//alarm on
		}

	/*опрос vibro*/
	else if (bit_is_set(PINC,PC3)) // если кнопка нажата (подключена к gnd, замыкается на vcc)
		{
		PORTC |= (1<<0);		//alarm on
		}

	/*опрос кнопки сброса*/
	else if (bit_is_set(PINC,PC5)) // если кнопка нажата (подключена к gnd, замыкается на vcc)
		{
		PORTC &= (~(1<<0));		//alarm off
		}
}
