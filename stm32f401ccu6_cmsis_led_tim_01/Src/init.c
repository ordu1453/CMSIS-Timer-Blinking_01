/*
 * init.c
 *
 *  Created on: 27 мар. 2024 г.
 *      Author: aordu
 */
#include "init.h"

void init_tim2(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->PSC = 80000-1;
	TIM2->ARR = 1000;

	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;

	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn,2);
}

void init_clk(void)
{
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY)){};

	// Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_PRFTEN;

	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_2WS;

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_5;

	RCC->CR |= RCC_CR_PLLON;

	while((RCC->CR & RCC_CR_PLLRDY) == 0) {};

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	while((RCC->CFGR &RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {};
}

void init_led(void)
{

	RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOCEN; 			// Clock enable

	GPIOC->MODER |= GPIO_MODER_MODER13_0;			// Mode register, 01 - Output

	LED_ON();
}

void init_btn(void)
{
	// PA0
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL0;
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->FTSR |= EXTI_FTSR_TR0;

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 1);
}

void TIM2_IRQHandler(void)
{
	static int k = 0;

	TIM2->SR &= ~TIM_SR_UIF;
	LED_SWAP();

	/*Led Switch*/
	switch (k)
	{
	case 0:
		TIM2->ARR = SHORT_DELAY;
		k = 1;
		break;
	case 1:
		TIM2->ARR = SHORT_DELAY;
		k = 2;
		break;
	case 2:
		TIM2->ARR = SHORT_DELAY;
		k = 3;
		break;
	case 3:
		TIM2->ARR = LONG_DELAY;
		k = 0;
		break;
	}
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR |=EXTI_PR_PR0;
	LED_SWAP();
}

void delay(int value)
{
	for (int i = 0; i < value; i++)
	{
		;;
	}
}
