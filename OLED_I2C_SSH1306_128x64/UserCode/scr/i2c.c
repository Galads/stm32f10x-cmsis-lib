/*
  ******************************************************************************
  *
	* @file    i2c.c
	* @file  	 i2c.h
  * @author  Gryumov Stanislav
  * @version V1.0.0
  * @date    26.01.2019
  * @brief   I2C  
  *			 Отладочная плата: STM32VLDISCOVERY
  *			 Реализованы отправка и приём данных по I2С.
	*			 Подключение датчика SCL - PB6, SDA - PB7
  *
  ******************************************************************************
  */

#include "i2c.h"


void i2c_Init(void)
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
		
	// Настройка параметров работы I2C-периферии МК
	I2C1->CR2 =   0x18;   		 // Частота тактирования модуля 24Мгц
	I2C1->CCR =   0x1E;        // Частота SCL 400К, старое значение 0x3C,
	I2C1->CCR &= ~I2C_CCR_FS;  // Standard mode
	I2C1->TRISE = 0x19;   		 // Rise time
	I2C1->CR1 |= I2C_CR1_ACK;  // Включить подтверждение
	I2C1->OAR1 = 0x10;          // Собственный адрес
	I2C1->CR1 |= I2C_CR1_PE;   // Включить переферию		
	
}

/************* I2C FUNCTION END *************/

/************* WRITE DATA FUNCTION BEGIN *************/

/* Функция записи в регистр
 * Входные параметры: адрес регистра, данные для записи
 */

void beginTransmission(uint8_t address)
{

		I2C1->CR1 |= I2C_CR1_START;
		while (!(I2C1->SR1 & I2C_SR1_SB));
		(void)(I2C1->SR1);	//добавил чтение регистра SR1

		// Пишем адрес устройства
		I2C1->DR = address;
		while((!(I2C1->SR1 & (I2C_SR1_AF | I2C_SR1_ADDR)))){};
		(void)(I2C1->SR1);  //добавил чтение регистра SR1
		(void)(I2C1->SR2);(void)(I2C1->SR2);	// Важно! Здесь необходимо чтение регистра SR2
		
}

void write(uint8_t byte)
{

		// Пишем данные в регистр
		I2C1->DR = byte;
		while (!(I2C1->SR1 & I2C_SR1_BTF));  /* Byte Transfer Finished */

}

/************* WRITE DATA FUNCTION END *************/