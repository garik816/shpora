#include "stm32f0xx.h"

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //включаем порт А
    
	GPIOA->MODER |= GPIO_MODER_MODER4_0; //режим порта на выход
	
	GPIOA->OTYPER = 0;  //режим подтяжки
	
	GPIOA->OSPEEDR = 0; //скорость
	
	while(1)
	{
		GPIOA->ODR ^= GPIO_ODR_4;       //мигаем PA 4
		for (int i=0; i<500000; i++);   //задерка
	}		
}
