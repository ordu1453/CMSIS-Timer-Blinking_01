/*
 * init.h
 *
 *  Created on: 27 мар. 2024 г.
 *      Author: aordu
 */

#ifndef INIT_H_
#define INIT_H_


#include "main.h"
#include "stm32f4xx.h"

#define LED_ON() 		GPIOC->BSRR = GPIO_BSRR_BS_13;
#define LED_OFF() 		GPIOC->BSRR = GPIO_BSRR_BR_13;
#define LED_SWAP() 		GPIOC->ODR ^= GPIO_ODR_ODR_13;
#define SHORT_DELAY 	100;
#define LONG_DELAY 		1500;

void init_clk(void);
void init_led(void);
void init_tim2(void);
void init_btn(void);
void TIM2_IRQHandler(void);
void delay(int value);


#endif /* INIT_H_ */
