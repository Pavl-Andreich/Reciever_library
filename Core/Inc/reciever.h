/*
 * reciever.h
 *
 *  Created on: Jul 30, 2025
 *      Author: pasha
 */

#ifndef INC_RECIEVER_H_
#define INC_RECIEVER_H_

#define SIGNAL_TIMEOUT_MS 100

#define TIMER1_OFFSET 16
#define TIMER2_OFFSET 25
#define TIMER3_OFFSET 7

#define TIMER1 TIM2
#define TIMER2 TIM3
#define TIMER3 TIM4

// !!!
// !!!
//определите свои объекты таймеров
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern volatile uint32_t ch1_period, ch1_pulse;
extern volatile uint32_t ch2_period, ch2_pulse;
extern volatile uint32_t ch3_period, ch3_pulse;
extern volatile uint32_t ch4_period, ch4_pulse;
extern volatile uint32_t ch5_period, ch5_pulse;
extern volatile uint32_t ch6_period, ch6_pulse;
extern volatile uint32_t ch1_last_update, ch2_last_update, ch3_last_update, ch4_last_update, ch5_last_update, ch6_last_update;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void CHANNEL_Init(void);

//
void check_signal (void);

#endif /* INC_RECIEVER_H_ */
