/*
* Описание взаимодействия с цифровым датчиком ds18b20 
* Для этого нужно инициализировать функцию Delay_Init();
* После инициализации можно считывать данные из функции temperature();
* Подключение ds18b20 к stm32 к порту A0 - A7   
*/
 
#include "1-wire.h"


void Delay_Init()
{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   
		TIM2->PSC     = 24 - 1;              
		TIM2->CR1     = TIM_CR1_OPM;          
}

void delay(uint32_t value)
{
		if (value >= 10000){TIM2->PSC = 24000 - 1; value /= 1000;}
		else{TIM2->PSC = 24 - 1;}
		TIM2->ARR = value;                  
		TIM2->CNT = 0;
		TIM2->CR1 = TIM_CR1_CEN;	      
		while((TIM2->SR & TIM_SR_UIF)==0){} 
		TIM2->SR &= ~TIM_SR_UIF;	      
}


void OneWireReset()
{
	
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
		GPIOA->CRL = (0x2 << NUMBER_PORT*4); 	// PA1
		GPIOA->BSRR = (GPIO_BSRR_BR0 << NUMBER_PORT);
		delay(480);
		GPIOA->BSRR = (GPIO_BSRR_BS0 << NUMBER_PORT);
		GPIOA->CRL = (0x8 << NUMBER_PORT*4); 	// PA1
		delay(30);
		while((GPIOA->IDR & (0x1 << NUMBER_PORT)) == 0);
		delay(15);

}

void OneWireWriteByte(uint8_t byte)
{
		
		GPIOA->CRL = (0x2 << NUMBER_PORT*4); 	// PA1
		GPIOA->BSRR = (GPIO_BSRR_BS0 << NUMBER_PORT); // PA1

		uint8_t volatile bit = 0;
		
		for (uint8_t i = 0 ;i < 8; i++)
		{
				bit = (1 << i);
				bit = ((byte & bit) >> i );

				if (bit)
				{
						GPIOA->BSRR = (GPIO_BSRR_BR0 << NUMBER_PORT); // PA1
						delay(15);
						GPIOA->BSRR = (GPIO_BSRR_BS0 << NUMBER_PORT);
						delay(45);

				}
				else
				{
						GPIOA->BSRR = (GPIO_BSRR_BR0 << NUMBER_PORT);
						delay(45);
						GPIOA->BSRR = (GPIO_BSRR_BS0 << NUMBER_PORT);
						delay(15);
				}
		}
	
}

uint8_t OneWireReadByte()
{
		uint8_t volatile byteRead = 0x0;

		for (uint8_t volatile i=0; i<8; i++)
		{	
				GPIOA->CRL = (0x2 << NUMBER_PORT*4); 	// PA1
				GPIOA->BSRR = (GPIO_BSRR_BR0 << NUMBER_PORT);
				for(uint8_t j=0;j<20;j++);
				GPIOA->CRL = (0x8 << NUMBER_PORT*4); 	// PA1
				for(uint16_t j=0;j<20;j++);	
				byteRead |= (((GPIOA->IDR & (0x1 << NUMBER_PORT)) >> (NUMBER_PORT)) << i);
				delay(60);
		}

		return byteRead;

}

float temperature()
{

			int16_t  temp;
			float  	 temp_cels;
			uint8_t  byteRead_H;
			uint8_t  byteRead_L;

			OneWireReset();
			OneWireWriteByte(0xCC);
			OneWireWriteByte(0x44);

			delay(1000000);

			OneWireReset();
			OneWireWriteByte(0xCC);
			OneWireWriteByte(0xBE);

			byteRead_L = OneWireReadByte();
			byteRead_H = OneWireReadByte();
			temp  =  ((byteRead_H << 8) | byteRead_L);
			temp_cels = temp * 0.0625;
	
			return temp_cels;

}

