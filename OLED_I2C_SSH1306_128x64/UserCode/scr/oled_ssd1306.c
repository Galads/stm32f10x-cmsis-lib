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

/** Функция вывода начала символа дисплей начало **/
void display_Сursor(uint8_t x, uint8_t y)
{
		int x1,x2;
		beginTransmission(address_Device);
		write(0x00);
		x1 = x%0x0f;
		x2 = x/0x10;
		write(0x03 + x1);	
		write(0x10 + x2);
		
		write(0xB0 + y);
		
		beginTransmission(address_Device);
		write(0x40);
	

}
/** Функция вывода начала символа дисплей конец **/

/**** Функция вывода строки на дисплей начало ****/

void display_Printf(char *str)
{

		for(int i=0; i<strlen(str);i++)
		{
		
			display_Write(str[i]);
		
		}

}

void display_Rus_Printf(char *str)
{
		for(int i=0; i<strlen(str);i++)
		{
			 if(i%2 != 0)
			 {
					display_Write(str[i] + 48);
			 }
		}
}

void setPixel(uint8_t x, uint8_t y)
{
		int x1,x2,y1,y2;
		beginTransmission(address_Device);
		write(0x00);
		x1 = x%0x0f;
		x2 = x/0x10;
		y1 = y/8;
		y2 = y%8;
		write(0x03 + x1);	
		write(0x10 + x2);
		write(0xB0 + y1);
		
		beginTransmission(address_Device);
		write(0x40);		
	  
		write(0x00 | (1 << y2));
}
/**** Функция вывода строки на дисплей конец****/

int main()
{
	
		i2c_Init();
		oled_Init();
		display_Clean();
		display_Сursor(26,3);

	  //display_Rus_Printf("ПРИВЕТ");
		
		uint8_t volatile word;
		word = 'п';
		word = 'р';
		word = 'т';

				
		
		while(1)
		{
		
			
		}
	
	
}
