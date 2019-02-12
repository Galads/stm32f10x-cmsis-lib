//#include "stm32f10x.h"          

//void TIM2_Init(void)
//{
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   
//  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	
//	
//	GPIOA->CRL &= ~GPIO_CRL_CNF0;  /* PA0 */  
//	GPIOA->CRL |= GPIO_CRL_CNF0_1;
//	
//	GPIOA->CRL &= ~GPIO_CRL_MODE0;
//	GPIOA->CRL |= GPIO_CRL_MODE0;
//	
//	GPIOA->CRL &= ~GPIO_CRL_CNF1;  /* PA1 */  
//	GPIOA->CRL |= GPIO_CRL_CNF1_1;
//	
//	GPIOA->CRL &= ~GPIO_CRL_MODE1;
//	GPIOA->CRL |= GPIO_CRL_MODE1;
//	
//	GPIOA->CRL &= ~GPIO_CRL_CNF2;  /* PA2 */  
//	GPIOA->CRL |= GPIO_CRL_CNF2_1;
//	
//	GPIOA->CRL &= ~GPIO_CRL_MODE2;
//	GPIOA->CRL |= GPIO_CRL_MODE2;
//	
//	TIM2->PSC = 240 - 1;
//	TIM2->ARR = 0xFF;
//	
//	TIM2->CCR1 = 0xFF; 
//	TIM2->CCR2 = 0xFF;
//	TIM2->CCR3 = 0xFF;
//	

//	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
//	TIM2->CCER |= TIM_CCER_CC1E;
//	TIM2->CCER &= ~TIM_CCER_CC1P; 
//	
//	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
//	TIM2->CCER |= TIM_CCER_CC2E;
//	TIM2->CCER &= ~TIM_CCER_CC2P;  
//	
//	TIM2->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
//	TIM2->CCER |= TIM_CCER_CC3E;
//	TIM2->CCER &= ~TIM_CCER_CC3P; 
//	
//	TIM2->CR1 &= ~TIM_CR1_DIR;
//	TIM2->CR1 |= TIM_CR1_CEN;
//}
//	

//void RGB( uint8_t R, uint8_t G, uint8_t B)
//{

//	TIM2->CCR1 = (0xFF - R);
//	TIM2->CCR2 = (0xFF - G);
//	TIM2->CCR3 = (0xFF - B);

//}

//void delay()
//{
//	for (int i=0;i<8000000;i++);
//}



//int main()
//{

//  	TIM2_Init();
//		RGB(0xff,0xff,0xff);
//	
//	while(1)
//	{
//		RGB(0xad,0xff,0x47);	
//		delay();
//	}
//	
//	
//}