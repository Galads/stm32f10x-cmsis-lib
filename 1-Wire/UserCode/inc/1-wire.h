#include "stm32f10x.h" 

#define   NUMBER_PORT ((uint8_t) 0 ) // номер порта A от A0 - A7 


void Delay_Init();
void delay(uint32_t value);
void OneWireReset();
void OneWireWriteByte(uint8_t byte);
uint8_t OneWireReadByte();
float temperature();