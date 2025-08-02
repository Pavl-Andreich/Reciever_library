/*
 * reciever.c
 *
 *  Created on: Jul 30, 2025
 *      Author: Pavel Lvov
 */
#include "main.h"
#include "reciever.h"


volatile uint32_t CH1_PERIOD = 0, CH1_PULSE = 0;
volatile uint32_t CH2_PERIOD = 0, CH2_PULSE = 0;
volatile uint32_t CH3_PERIOD = 0, CH3_PULSE = 0;
volatile uint32_t CH4_PERIOD = 0, CH4_PULSE = 0;
volatile uint32_t CH5_PERIOD = 0, CH5_PULSE = 0;
volatile uint32_t CH6_PERIOD = 0, CH6_PULSE = 0;
volatile uint32_t CH1_LAST_UPDATE = 0, CH2_LAST_UPDATE = 0, CH3_LAST_UPDATE = 0, CH4_LAST_UPDATE = 0, CH5_LAST_UPDATE = 0, CH6_LAST_UPDATE = 0;

void Rec_Channel_Init(void){
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
    	if (/*htim->Instance->SR & TIM_SR_CC1IF*/ 1) {
    		htim->Instance->SR &= ~TIM_SR_CC1IF;
    		//htim->Instance->CNT = 0; //сброс счетчика
    	    // Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
    	    CH1_PERIOD = (htim->Instance->CCR1) + TIMER1_OFFSET;
    	    CH1_PULSE = (htim->Instance->CCR2) + TIMER1_OFFSET;
    	    //ch1_last_update = now1;
    	}
    	if (htim->Instance->SR & TIM_SR_CC3IF) {
    		htim->Instance->SR &= ~TIM_SR_CC3IF;
    		htim->Instance->CNT = 0; //сброс счетчика
    	    // Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
    		CH2_PERIOD = (htim->Instance->CCR3) + TIMER1_OFFSET;
    		CH2_PULSE = (htim->Instance->CCR4) + TIMER1_OFFSET;
    		CH2_LAST_UPDATE = now1;
    	}
    }
    if (htim->Instance == TIMER2)
	{
		uint32_t now2 = HAL_GetTick();
		if (/*htim->Instance->SR & TIM_SR_CC1IF*/ 1) {
			htim->Instance->SR &= ~TIM_SR_CC1IF;
			//htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			CH3_PERIOD = (htim->Instance->CCR1) + TIMER2_OFFSET;
			CH3_PULSE = (htim->Instance->CCR2) + TIMER2_OFFSET;
			//CH3_LAST_UPDATE = now2;
		}
		if (htim->Instance->SR & TIM_SR_CC3IF) {
			htim->Instance->SR &= ~TIM_SR_CC3IF;
			htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			CH4_PERIOD = (htim->Instance->CCR3) + TIMER2_OFFSET;
			CH4_PULSE = (htim->Instance->CCR4) + TIMER2_OFFSET;
			CH4_LAST_UPDATE = now2;
		}
	}
    if (htim->Instance == TIMER3)
	{
		uint32_t now3 = HAL_GetTick();
		if (/*htim->Instance->SR & TIM_SR_CC1IF*/ 1) {
			htim->Instance->SR &= ~TIM_SR_CC1IF;
			//htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			CH5_PERIOD = (htim->Instance->CCR1) + TIMER3_OFFSET;
			CH5_PULSE = (htim->Instance->CCR2) + TIMER3_OFFSET;
			//CH5_LAST_UPDATE = now3;
		}
		if (htim->Instance->SR & TIM_SR_CC3IF) {
			htim->Instance->SR &= ~TIM_SR_CC3IF;
			htim->Instance->CNT = 0; //сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			CH6_PERIOD = (htim->Instance->CCR3) + TIMER3_OFFSET;
			CH6_PULSE = (htim->Instance->CCR4) + TIMER3_OFFSET;
			CH6_LAST_UPDATE = now3;
		}
	}
}

void check_signal (void){
	uint32_t recently_time = HAL_GetTick();
	if ((recently_time - CH2_LAST_UPDATE) > SIGNAL_TIMEOUT_MS) {
		CH1_PULSE = 0;
		CH2_PULSE = 0;
	}
	if ((recently_time - CH4_LAST_UPDATE) > SIGNAL_TIMEOUT_MS) {
		CH3_PULSE = 0;
		CH4_PULSE = 0;
	}
	if ((recently_time - CH6_LAST_UPDATE) > SIGNAL_TIMEOUT_MS) {
		CH5_PULSE = 0;
		CH6_PULSE = 0;
	}
}


