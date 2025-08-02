/*
 * reciever.h
 * Библиотека для приема 6-канальных ШИМ-сигналов
 * Особенности:
 *   - Поддержка трех таймеров
 *   - Автоматическое определение периода и ширины импульса
 *   - Таймаут при потере сигнала
 *   - При пропадании сигнала с одного канала таймера обнуляются оба значения ШИМ сигналов приходящих на этот таймер
 *
 * Версия: 1.1
 * Автор: Pavel Lvov
 * Дата создания: 30.07.2025
 */

#ifndef INC_RECIEVER_H_
#define INC_RECIEVER_H_

/* Для каждого таймера (сама система настрена на 72 МГц, тогда получаем значения в мкс):
 * Prescaler: 72-1 (для 1 МГц тактовой частоты)
 * Counter Period: 65535
 * Clock Source: Internal Clock
 * TIMx global interrupt: Enable
 * Режим CH1 или CH3: Input Capture direct mode
 * Режим CH2 или CH4: Input Capture indirect mode
 * Канал 1: Rising Edge
 * Канал 2: Falling Edge
 * Канал 3: Rising Edge
 * Канал 4: Falling Edge
 * !!! подтягиваем ножки ввода к земле (GPIO: Pull-down) !!!
 *
 */

//-------------------------------------DEFINES-------------------------------------//
#define SIGNAL_TIMEOUT_MS 100 				// Таймаут потери сигнала (мс)

// Настройка используемых таймеров (ИЗМЕНИТЕ ПОД ВАШУ КОНФИГУРАЦИЮ)
#define TIMER1 TIM2  						// Таймер для каналов 1-2
#define TIMER2 TIM3  						// Таймер для каналов 3-4
#define TIMER3 TIM4  						// Таймер для каналов 5-6

// Калибровочные смещения для каждого таймера (корректировка погрешности измерения)
#define TIMER1_OFFSET 16  					// Смещение для TIMER1
#define TIMER2_OFFSET 25  					// Смещение для TIMER2
#define TIMER3_OFFSET 7   					// Смещение для TIMER3

// задайте свои переменные
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

//-------------------------------------VARIABLES-------------------------------------//
//определите объекты своих таймеров
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

// Глобальные переменные для доступа к данным ШИМ (обновляются автоматически)
extern volatile uint32_t CH1_PERIOD, CH1_PULSE;	// Канал 1: период (мкс), ширина импульса (мкс)
extern volatile uint32_t CH2_PERIOD, CH2_PULSE;	// Канал 2: период (мкс), ширина импульса (мкс)
extern volatile uint32_t CH3_PERIOD, CH3_PULSE;	// Канал 3: период (мкс), ширина импульса (мкс)
extern volatile uint32_t CH4_PERIOD, CH4_PULSE;	// Канал 4: период (мкс), ширина импульса (мкс)
extern volatile uint32_t CH5_PERIOD, CH5_PULSE; // Канал 5: период (мкс), ширина импульса (мкс)
extern volatile uint32_t CH6_PERIOD, CH6_PULSE; // Канал 6: период (мкс), ширина импульса (мкс)
// Время последнего обновления (для проверки таймаута)
extern volatile uint32_t CH1_LAST_UPDATE, CH2_LAST_UPDATE, CH3_LAST_UPDATE;
extern volatile uint32_t CH4_LAST_UPDATE, CH5_LAST_UPDATE, CH6_LAST_UPDATE;

//-------------------------------------FUNCTIONS-------------------------------------//
/**
 * @brief Инициализация каналов приема
 * @note Должна вызываться после инициализации таймеров
 */
void Rec_Channel_Init(void);

/**
 * @brief Стандартная функция библиотеки HAL
 * @note вызывается после обработчика прерывания
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

/**
 * @brief Проверка актуальности сигналов
 * @note Автоматически обнуляет каналы при превышении таймаута
 *       Должна вызываться периодически (например, в основном цикле)
 */
void check_signal (void);

#endif /* INC_RECIEVER_H_ */
