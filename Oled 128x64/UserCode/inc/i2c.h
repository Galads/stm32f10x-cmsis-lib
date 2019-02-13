#include "stm32f10x.h"   


void i2c_Init(void);
void beginTransmission(uint8_t address);
void write(uint8_t byte);