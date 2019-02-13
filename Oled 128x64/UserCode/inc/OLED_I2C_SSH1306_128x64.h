#include "stm32f10x.h"   
#include "i2c.h"
#include "string.h"

#define address_Device 			((uint8_t)0x78) // адрес подключаемого устройства по шине I2C

void oled_Init(void);
void display_Clean();
void display_Write(uint8_t word);
void display_Write_Negative(uint8_t word);
void display_Cursor(uint8_t x, uint8_t y);
void display_Printf(uint8_t x, uint8_t y, char *str);
void setPixel(uint8_t x, uint8_t y);
