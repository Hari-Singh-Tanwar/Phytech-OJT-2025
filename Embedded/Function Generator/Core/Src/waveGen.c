#include "waveGen.h"

extern TIM_HandleTypeDef htim2;
extern DAC_HandleTypeDef hdac1;

void sinWave()
{
    HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
    for (int i = 0; i < SAMPLES; i++)
    {
        wave_lut[i] = (uint32_t)((sin((2 * PI * i) / SAMPLES) + 1) * 2047.5);
    }
    HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t *)wave_lut, SAMPLES, DAC_ALIGN_12B_R);
}

void squareWave()
{
    HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
    for (int i = 0; i < SAMPLES; i++)
    {
        wave_lut[i] = (i < SAMPLES / 2) ? 4095 : 0;
    }
    HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t *)wave_lut, SAMPLES, DAC_ALIGN_12B_R);
}

void triangleWave()
{
    HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
    uint16_t half_samples = SAMPLES / 2;
    for (int i = 0; i < half_samples; i++)
    {
        wave_lut[i] = (uint32_t)((i * 4095) / half_samples);
    }
    for (int i = 0; i < half_samples; i++)
    {
        wave_lut[i + half_samples] = (uint32_t)(((half_samples - i) * 4095) / half_samples);
    }
    HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t *)wave_lut, SAMPLES, DAC_ALIGN_12B_R);
}

void sawtoothWave()
{
    HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);

    for (int i = 0; i < SAMPLES; i++)
    {
        wave_lut[i] = (uint32_t)((i * 4095.0) / SAMPLES);
    }
    HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t *)wave_lut, SAMPLES, DAC_ALIGN_12B_R);
}

bool wave_freq(uint16_t frequency)
{
    if (frequency < 1 || frequency > 10000) // Frequency range: 1Hz to 1kHz
    {
        return false; // Invalid frequency
    }

    // Calculate the timer period for the desired frequency
    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq() * 1; // Assuming APB1 prescaler is not 1
    uint32_t prescaler = 0;
    uint32_t period = (timer_clock / frequency) - 1;

    // Find suitable prescaler and period values
    while (period > 0xFFFF) // Timer period must fit in 16 bits
    {
        prescaler++;
        period = (timer_clock / (frequency * (prescaler + 1))) - 1;
        if (prescaler > 0xFFFF) // Prescaler must also fit in 16 bits
        {
            return false; // Cannot achieve desired frequency
        }
    }

    HAL_TIM_Base_Stop(&htim2);
    htim2.Instance->PSC = prescaler;
    htim2.Instance->ARR = period;
    HAL_TIM_Base_Start(&htim2);

    return true; // Frequency set successfully
}