/*
  ******************************************************************************
  *
	* @file    MPU6050.c
	* @file    MPU6050.h
  * @author  Gryumov Stanislav
  * @version V1.0.0
  * @date    26.01.2019
  * @brief   Дипломная работа
  *			 Отладочная плата: STM32VLDISCOVERY
  *			 Реализованы отправка и приём данных по I2С.
	*			 Подключение датчика SCL - PB6, SDA - PB7
  *
  ******************************************************************************
  */
#include "stm32f10x.h"   
#include "oled_ssd1306.h"
#define Address_Write 			((uint16_t)0x78)

/************* I2C FUNCTION BEGIN *************/

void I2C1_Init(void)
{
  //включаем тактирование портов и модуля I2C
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // включаем тактирование порта B
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // включаем тактирование I2C1
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // включаем тактирование альтернативных функций
	
	// настроим PB6 - SCL
	GPIOB->CRL &= ~GPIO_CRL_MODE6;				// Занулили биты
	GPIOB->CRL |= GPIO_CRL_MODE6_1;				// Output mode, speed 2 MHz (10)
	
	GPIOB->CRL &= ~GPIO_CRL_CNF6;					// Занулили биты
	GPIOB->CRL |= GPIO_CRL_CNF6;					// Alternate function output Open-drain (11)
		
	// настроим PB7 - SDA
	GPIOB->CRL &= ~GPIO_CRL_MODE7;				// Занулили биты
	GPIOB->CRL |= GPIO_CRL_MODE7_1;				// Output mode, speed 2 MHz (10)
	
	GPIOB->CRL &= ~GPIO_CRL_CNF7;					// Занулили биты
	GPIOB->CRL |= GPIO_CRL_CNF7;					// Alternate function output Open-drain (11)
	
	//настраиваем модуль в режим I2C
	
	// Настройка параметров работы I2C-периферии МК
	I2C1->CR2 =   0x18;   		 // Частота тактирования модуля 24Мгц
	I2C1->CCR =   0x1E;        // Частота SCL 400К, старое значение 0x3C,
	I2C1->CCR &= ~I2C_CCR_FS;  // Standard mode
	I2C1->TRISE = 0x19;   		 // Rise time
	I2C1->CR1 |= I2C_CR1_ACK;  // Включить подтверждение
	I2C1->OAR1 = 0x10;          // Собственный адрес
	I2C1->CR1 |= I2C_CR1_PE;   // Включить переферию		
	
	// формирование сигнала старт

}

/************* I2C FUNCTION END *************/

/************* WRITE DATA FUNCTION BEGIN *************/

/* Функция записи в регистр
 * Входные параметры: адрес регистра, данные для записи
 */

void AddressDeviceWrite(uint8_t Register_Sensor)
{

		I2C1->CR1 |= I2C_CR1_START;
		while (!(I2C1->SR1 & I2C_SR1_SB));
		(void)(I2C1->SR1);	//добавил чтение регистра SR1

		// Пишем адрес устройства
		I2C1->DR = Register_Sensor;
		while((!(I2C1->SR1 & (I2C_SR1_AF | I2C_SR1_ADDR)))){};
		(void)(I2C1->SR1);  //добавил чтение регистра SR1
		(void)(I2C1->SR2);(void)(I2C1->SR2);	// Важно! Здесь необходимо чтение регистра SR2
		
}

void DataWrite(uint8_t data)
{

		// Пишем данные в регистр
		I2C1->DR = data;
		while (!(I2C1->SR1 & I2C_SR1_BTF));  /* Byte Transfer Finished */

}

/************* WRITE DATA FUNCTION END *************/



void OLED_Init(void)
{
			//конфигурация датчика
			AddressDeviceWrite(0x78);
			DataWrite(0x00);
			DataWrite(0xAE);
			DataWrite(0xD5);
			DataWrite(0x80);
			DataWrite(0xA8);
			DataWrite(0x3F);
			DataWrite(0xD3);
			DataWrite(0x00);
			DataWrite(0x40);
			DataWrite(0x8D);
			DataWrite(0x14);
			DataWrite(0x20);
			DataWrite(0x02);
			DataWrite(0xA1);
			DataWrite(0xC8);
			DataWrite(0xDA);
			DataWrite(0x12);
			DataWrite(0x81);
			DataWrite(0xCF);
			DataWrite(0xD9);
			DataWrite(0xF1);
			DataWrite(0xDB);
			DataWrite(0x40);
			DataWrite(0x2E);
			DataWrite(0xA4);
			DataWrite(0xA6);
			DataWrite(0xAF);		
			
}

void Display_Clean()
{
	for (int i=0; i<8;i++)
	{
	
	 AddressDeviceWrite(0x78);
	 DataWrite(0x00);
	 DataWrite(0x10);
	 DataWrite(0x02);
	 DataWrite(0xB0 + i);
	
	 AddressDeviceWrite(0x78);
	 DataWrite(0x40);//установка столбца
	 
			for(int j=0;j<128;j++)
			{
				
			 DataWrite(0x00);
			}
	}
	
		 
}

void Display_Write(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e)
{



		
		DataWrite(a);
		DataWrite(b);
		DataWrite(c);
		DataWrite(d);
		DataWrite(e);
		DataWrite(0x00);
		DataWrite(0x00);
	 
}

int main()
{

	I2C1_Init();
	OLED_Init();
	OLED_Init();
	Display_Clean();
	
		AddressDeviceWrite(0x78);
		DataWrite(0x00);
		DataWrite(0x10);
		DataWrite(0x02);
		DataWrite(0xB0);

		AddressDeviceWrite(0x78);
		DataWrite(0x40);
	
		Display_Write(0x46, 0x49, 0x49, 0x49, 0x31);
		Display_Write(0x01, 0x01, 0x7F, 0x01, 0x01);
		Display_Write(0x7E, 0x11, 0x11, 0x11, 0x7E);
		Display_Write(0x46, 0x49, 0x49, 0x49, 0x31);
		
		Display_Write(0x00, 0x00, 0x00, 0x00, 0x00);
		
		Display_Write(0x3E, 0x41, 0x49, 0x49, 0x7A);
		Display_Write(0x7F, 0x09, 0x19, 0x29, 0x46);
		Display_Write(0x07, 0x08, 0x70, 0x08, 0x07);
		Display_Write(0x3F, 0x40, 0x40, 0x40, 0x3F);
		Display_Write(0x7F, 0x02, 0x0C, 0x02, 0x7F);
		Display_Write(0x3E, 0x41, 0x41, 0x41, 0x3E);
		Display_Write(0x1F, 0x20, 0x40, 0x20, 0x1F);
		
	while(1)
	{

	}
	
	
}

