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

#define CH1_LAST_UPDATE ch1_last_update
#define CH2_LAST_UPDATE ch2_last_update
#define CH3_LAST_UPDATE ch3_last_update
#define CH4_LAST_UPDATE ch4_last_update
#define CH5_LAST_UPDATE ch5_last_update
#define CH6_LAST_UPDATE ch6_last_update

#define CH1_PERIOD ch1_period
#define CH2_PERIOD ch2_period
#define CH3_PERIOD ch3_period
#define CH4_PERIOD ch4_period
#define CH4_PERIOD ch5_period
#define CH6_PERIOD ch6_period

#define CH1_PULSE ch1_pulse
#define CH2_PULSE ch2_pulse
#define CH3_PULSE ch3_pulse
#define CH4_PULSE ch4_pulse
#define CH5_PULSE ch5_pulse
#define CH6_PULSE ch6_pulse

// !!!
// !!!
//определите свои объекты таймеров
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern volatile uint32_t CH1_PERIOD, CH1_PULSE;
extern volatile uint32_t CH2_PERIOD, CH2_PULSE;
extern volatile uint32_t CH3_PERIOD, CH3_PULSE;
extern volatile uint32_t CH4_PERIOD, CH4_PULSE;
extern volatile uint32_t CH5_PERIOD, CH5_PULSE;
extern volatile uint32_t CH6_PERIOD, CH6_PULSE;
extern volatile uint32_t CH1_LAST_UPDATE, CH2_LAST_UPDATE, CH3_LAST_UPDATE, CH4_LAST_UPDATE, CH5_LAST_UPDATE, CH6_LAST_UPDATE;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void Rec_Channel_Init(void);

//
void check_signal (void);

#endif /* INC_RECIEVER_H_ */
