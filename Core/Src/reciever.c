/*
 * reciever.c
 *
 *  Created on: Jul 30, 2025
 *      Author: Pavel Lvov
 */
#include "main.h"
#include "reciever.h"


volatile uint32_t ch1_period = 0, ch1_pulse = 0;
volatile uint32_t ch2_period = 0, ch2_pulse = 0;
volatile uint32_t ch3_period = 0, ch3_pulse = 0;
volatile uint32_t ch4_period = 0, ch4_pulse = 0;
volatile uint32_t ch5_period = 0, ch5_pulse = 0;
volatile uint32_t ch6_period = 0, ch6_pulse = 0;
volatile uint32_t ch1_last_update = 0, ch2_last_update = 0, ch3_last_update = 0, ch4_last_update = 0, ch5_last_update = 0, ch6_last_update = 0;

void REC_CHANNEL_Init(void){
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_4);
	  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_4);
	  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_4);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{




    if (htim->Instance == TIMER1)
    {
    	uint32_t now1 = HAL_GetTick();
    	if (htim->Instance->SR & TIM_SR_CC1IF) {
    		htim->Instance->SR &= ~TIM_SR_CC1IF;
    		//htim->Instance->CNT = 0; //сброс счетчика
    	    // Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
    	    ch1_period = (htim->Instance->CCR1) + TIMER1_OFFSET;
    	    ch1_pulse = (htim->Instance->CCR2) + TIMER1_OFFSET;
    	    //ch1_last_update = now1;
    	}
    	if (htim->Instance->SR & TIM_SR_CC3IF) {
    		htim->Instance->SR &= ~TIM_SR_CC3IF;
    		htim->Instance->CNT = 0; //сброс счетчика
    	    // Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
    		ch2_period = (htim->Instance->CCR3) + TIMER1_OFFSET;
    		ch2_pulse = (htim->Instance->CCR4) + TIMER1_OFFSET;
    		ch2_last_update = now1;
    	}
    }
    if (htim->Instance == TIMER2)
	{
		uint32_t now2 = HAL_GetTick();
		if (htim->Instance->SR & TIM_SR_CC1IF) {
			htim->Instance->SR &= ~TIM_SR_CC1IF;
			htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			ch3_period = (htim->Instance->CCR1) + TIMER2_OFFSET;
			ch3_pulse = (htim->Instance->CCR2) + TIMER2_OFFSET;
			//ch3_last_update = now2;
		}
		if (htim->Instance->SR & TIM_SR_CC3IF) {
			htim->Instance->SR &= ~TIM_SR_CC3IF;
			htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			ch4_period = (htim->Instance->CCR3) + TIMER2_OFFSET;
			ch4_pulse = (htim->Instance->CCR4) + TIMER2_OFFSET;
			ch4_last_update = now2;
		}
	}
    if (htim->Instance == TIMER3)
	{
		uint32_t now3 = HAL_GetTick();
		if (htim->Instance->SR & TIM_SR_CC1IF) {
			htim->Instance->SR &= ~TIM_SR_CC1IF;
			htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			ch5_period = (htim->Instance->CCR1) + TIMER3_OFFSET;
			ch5_pulse = (htim->Instance->CCR2) + TIMER3_OFFSET;
			//ch5_last_update = now3;
		}
		if (htim->Instance->SR & TIM_SR_CC3IF) {
			htim->Instance->SR &= ~TIM_SR_CC3IF;
			htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			ch6_period = (htim->Instance->CCR3) + TIMER3_OFFSET;
			ch6_pulse = (htim->Instance->CCR4) + TIMER3_OFFSET;
			ch6_last_update = now3;
		}
	}
}

void check_signal (void){
	uint32_t recently_time = HAL_GetTick();
	if ((recently_time - ch1_last_update) > SIGNAL_TIMEOUT_MS) {
		ch1_pulse = 0;
	}
	if ((recently_time - ch2_last_update) > SIGNAL_TIMEOUT_MS) {
		ch2_pulse = 0;
	}
	if ((recently_time - ch3_last_update) > SIGNAL_TIMEOUT_MS) {
		ch3_pulse = 0;
	}
	if ((recently_time - ch4_last_update) > SIGNAL_TIMEOUT_MS) {
		ch4_pulse = 0;
	}
	if ((recently_time - ch5_last_update) > SIGNAL_TIMEOUT_MS) {
		ch5_pulse = 0;
	}
	if ((recently_time - ch6_last_update) > SIGNAL_TIMEOUT_MS) {
		ch6_pulse = 0;
	}
}


