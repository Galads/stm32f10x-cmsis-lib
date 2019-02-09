/*
  ******************************************************************************
  *
	* @file    oled_ssd1306.c
	* @file    oled_ssd1306.h
  * @author  Gryumov Stanislav
  * @version V1.0.1
  * @date    26.01.2019
  * @brief   OLED Дисплей 
  *			 Отладочная плата: STM32VLDISCOVERY
  *			 Реализованы отправка и приём данных по I2С.
	*			 Подключение датчика SCL - PB6, SDA - PB7
  *
  ******************************************************************************
  */

#include "oled_ssd1306.h"

/************* Инициализация дисплея начало *************/
void oled_Init(void)
{
		beginTransmission(address_Device); // адресс устройства
		for (int i=0;i<28;i++)
		{
				write(oled_init[i]);
		}		
}
/************* Инициализация дисплея конец *************/

/************* Функция отчистки дисплея начало *************/
void display_Clean()
{
	for (int i=0; i<8;i++)
	{
	
			beginTransmission(address_Device);
			write(0x00);
			write(0x10);
			write(0x02);
			write(0xB0 + i);

			beginTransmission(address_Device);
			write(0x40);//установка столбца

			for(int j=0;j<128;j++)
			{
					write(0x00);
			}
	}	
		 
}
/************* Функция отчистки дисплея конец *************/

/******** Функция вывода символа на дисплей начало ********/
void display_Write(uint8_t word)
{		
		write(fontTable[word][0]);
		write(fontTable[word][1]);
		write(fontTable[word][2]);
		write(fontTable[word][3]);
		write(fontTable[word][4]);
		write(0x00); // Расстояние между буквами
}
/******** Функция вывода символа на дисплей конец ********/

/** Функция вывода негативного символа на дисплей начало **/
void display_Write_Negative(uint8_t word)
{

		write(~(fontTable[word][0] << 1));
		write(~(fontTable[word][1] << 1));
		write(~(fontTable[word][2] << 1));
		write(~(fontTable[word][3] << 1));
		write(~(fontTable[word][4] << 1));
		write(~0x00); // Расстояние между буквами

}
/** Функция вывода негативного символа на дисплей конец **/

/** Функция вывода начала строки дисплей начало **/
void display_Сursor(uint8_t x, uint8_t y)
{
	
		beginTransmission(address_Device);
		write(0x00);
		write(0x10);
		write(0x02);
		write(0xB0 + y);
	
		beginTransmission(address_Device);
		write(0x40);

}
/** Функция вывода начала строки дисплей конец **/

int main()
{

		i2c_Init();
		oled_Init();
		display_Clean();

		display_Сursor(20,3);
	
		display_Write_Negative('S');
		display_Write_Negative('T');
		display_Write_Negative('A');
		display_Write_Negative('S');
		display_Write(' ');
		display_Write('S');
		display_Write('T');
		display_Write('A');
		display_Write('S');
				
	while(1)
	{

	}
	
	
}

