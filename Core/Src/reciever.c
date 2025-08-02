/*
 * reciever.c
 * Реализация приема 6-канальных ШИМ-сигналов
 * Особенности:
 *   - Использование режима Input Capture
 *   - Автоматический сброс при потере сигнала
 *   - Корректировка погрешности измерения через смещения
 *
 * Версия: 1.1
 * Автор: Pavel Lvov
 * Дата создания: 30.07.2025
 */
#include "main.h"
#include "reciever.h"

//-------------------------------------GLOBAL VARIABLS-------------------------------------//
// Значения ШИМ для каждого канала (обновляются в прерываниях)
volatile uint32_t CH1_PERIOD = 0, CH1_PULSE = 0;
volatile uint32_t CH2_PERIOD = 0, CH2_PULSE = 0;
volatile uint32_t CH3_PERIOD = 0, CH3_PULSE = 0;
volatile uint32_t CH4_PERIOD = 0, CH4_PULSE = 0;
volatile uint32_t CH5_PERIOD = 0, CH5_PULSE = 0;
volatile uint32_t CH6_PERIOD = 0, CH6_PULSE = 0;

// Время последнего обновления (системные тики)
volatile uint32_t CH1_LAST_UPDATE = 0, CH2_LAST_UPDATE = 0, CH3_LAST_UPDATE = 0;
volatile uint32_t CH4_LAST_UPDATE = 0, CH5_LAST_UPDATE = 0, CH6_LAST_UPDATE = 0;

//-------------------------------------FUNCTIONS-------------------------------------//
/**
 * @brief Инициализация каналов приема ШИМ
 * @note Запускает захват сигналов на всех каналах
 *       Для каналов 1,3,5 включены прерывания (период)
 *       Для каналов 2,4,6 используется прямой захват (ширина импульса)
 *       (запускаем нужные каналы на выбранных таймерах (каналы работают только в паре 1-2 и 3-4)
 */
void Rec_Channel_Init(void){
	  // Таймер 1 - сигналы 1-2
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_4);

	  // Таймер 2 - сигналы 3-4
	  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_4);

	  // Таймер 3 - сигналы 5-6
	  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_4);
}


/**
 * @brief Callback-функция захвата сигнала
 * @param htim Указатель на обработчик таймера
 * @note Автоматически вызывается при захвате фронта сигнала
 * 		для адаптации кода нужно изменить макросы таймеров и !
 * 		! изменить значения регистров (TIM_SR_CCxIF и ССRx) в зависимости от используемых каналов:
 * 		если используется пара 1-2 то TIM_SR_CC1IF и CCR1 + CCR2, если 3-4 -- TIM_SR_CC3IF и CCR3 + CCR4
 *
 * 		так же если используется только каналы 1-2, то необходимо раскоментировать строчки /* */  //кроме того что в условии if()

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIMER1)
    {
    	uint32_t now1 = HAL_GetTick();
    	if (/*htim->Instance->SR & TIM_SR_CC1IF*/ 1) {
    		htim->Instance->SR &= ~TIM_SR_CC1IF;
    		/*htim->Instance->CNT = 0;*/ 		//сброс счетчика
    	    // Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
    	    CH1_PERIOD = (htim->Instance->CCR1) + TIMER1_OFFSET;
    	    CH1_PULSE = (htim->Instance->CCR2) + TIMER1_OFFSET;
    	    /*CH1_LAST_UPDATE = now1;*/
    	}
    	if (htim->Instance->SR & TIM_SR_CC3IF) {
    		htim->Instance->SR &= ~TIM_SR_CC3IF;
    		htim->Instance->CNT = 0; 			//сброс счетчика
    	    // Signal 2: Чтение периода (CCR3) и ширины импульса (CCR4)
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
			/*htim->Instance->CNT = 0;*/ 		//сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			CH3_PERIOD = (htim->Instance->CCR1) + TIMER2_OFFSET;
			CH3_PULSE = (htim->Instance->CCR2) + TIMER2_OFFSET;
			/*CH3_LAST_UPDATE = now2;*/
		}
		if (htim->Instance->SR & TIM_SR_CC3IF) {
			htim->Instance->SR &= ~TIM_SR_CC3IF;
			htim->Instance->CNT = 0; 			//сброс счетчика
			// Signal 2: Чтение периода (CCR3) и ширины импульса (CCR4)
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
			/*htim->Instance->CNT = 0;*/ 		//сброс счетчика
			// Signal 1: Чтение периода (CCR1) и ширины импульса (CCR2)
			CH5_PERIOD = (htim->Instance->CCR1) + TIMER3_OFFSET;
			CH5_PULSE = (htim->Instance->CCR2) + TIMER3_OFFSET;
			/*CH5_LAST_UPDATE = now3;*/
		}
		if (htim->Instance->SR & TIM_SR_CC3IF) {
			htim->Instance->SR &= ~TIM_SR_CC3IF;
			htim->Instance->CNT = 0; 			//сброс счетчика
			// Signal 2: Чтение периода (CCR3) и ширины импульса (CCR4)
			CH6_PERIOD = (htim->Instance->CCR3) + TIMER3_OFFSET;
			CH6_PULSE = (htim->Instance->CCR4) + TIMER3_OFFSET;
			CH6_LAST_UPDATE = now3;
		}
	}
}

/**
 * @brief Проверка актуальности сигналов
 * @note Обнуляет значения каналов при превышении таймаута
 *       Должна вызываться периодически (рекомендуется >10 Гц)
 */
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


