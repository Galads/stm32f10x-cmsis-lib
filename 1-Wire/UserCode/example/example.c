#include "1-wire.h"

int main()
{

	Delay_Init();
	
	float volatile  temp_cels;
	
	while(1)
	{
		
	 temp_cels = temperature();

	}
	
}