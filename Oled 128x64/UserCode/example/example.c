#include "OLED_I2C_SSH1306_128x64.h"

int main()
{
	
		i2c_Init();
		oled_Init();
		display_Clean();
		
	  display_Printf(16,3,"������� �������");
				
		while(1)
		{
		
			
		}
	
	
}