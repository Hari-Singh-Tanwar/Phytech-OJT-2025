/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac1;
DMA_HandleTypeDef hdma_dac1_ch1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint32_t sine_lut[200] = {

    2048, 2112, 2176, 2240, 2304, 2368, 2431, 2494, 2557, 2619, 2680, 2741, 2801, 2861, 2919, 2977, 3034, 3090, 3145, 3198, 3251, 3302, 3353, 3402, 3449, 3495, 3540, 3583, 3625, 3665, 3704, 3741, 3776, 3810, 3842, 3872, 3900, 3927, 3951, 3974, 3995, 4014, 4031, 4046, 4059, 4070, 4079, 4086, 4091, 4094, 4095, 4094, 4091, 4086, 4079, 4070, 4059, 4046, 4031, 4014, 3995, 3974, 3951, 3927, 3900, 3872, 3842, 3810, 3776, 3741, 3704, 3665, 3625, 3583, 3540, 3495, 3449, 3402, 3353, 3302, 3251, 3198, 3145, 3090, 3034, 2977, 2919, 2861, 2801, 2741, 2680, 2619, 2557, 2494, 2431, 2368, 2304, 2240, 2176, 2112, 2048, 1983, 1919, 1855, 1791, 1727, 1664, 1601, 1538, 1476, 1415, 1354, 1294, 1234, 1176, 1118, 1061, 1005, 950, 897, 844, 793, 742, 693, 646, 600, 555, 512, 470, 430, 391, 354, 319, 285, 253, 223, 195, 168, 144, 121, 100, 81, 64, 49, 36, 25, 16, 9, 4, 1, 0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 168, 195, 223, 253, 285, 319, 354, 391, 430, 470, 512, 555, 600, 646, 693, 742, 793, 844, 897, 950, 1005, 1061, 1118, 1176, 1234, 1294, 1354, 1415, 1476, 1538, 1601, 1664, 1727, 1791, 1855, 1919, 1983};


// uint32_t sine_lut[1000] = {
// 2048, 2060, 2073, 2086, 2099, 2112, 2125, 2138, 2150, 2163, 2176, 2189, 2202, 2215, 2227, 2240, 2253, 2266, 2279, 2291, 2304, 2317, 2330, 2342, 2355, 2368, 2380, 2393, 2406, 2419, 2431, 2444, 2456, 2469, 2482, 2494, 2507, 2519, 2532, 2544, 2557, 2569, 2582, 2594, 2606, 2619, 2631, 2643, 2656, 2668, 2680, 2692, 2705, 2717, 2729, 2741, 2753, 2765, 2777, 2789, 2801, 2813, 2825, 2837, 2849, 2861, 2872, 2884, 2896, 2908, 2919, 2931, 2942, 2954, 2966, 2977, 2988, 3000, 3011, 3023, 3034, 3045, 3056, 3068, 3079, 3090, 3101, 3112, 3123, 3134, 3145, 3155, 3166, 3177, 3188, 3198, 3209, 3220, 3230, 3241, 3251, 3261, 3272, 3282, 3292, 3302, 3313, 3323, 3333, 3343, 3353, 3363, 3372, 3382, 3392, 3402, 3411, 3421, 3430, 3440, 3449, 3458, 3468, 3477, 3486, 3495, 3504, 3513, 3522, 3531, 3540, 3549, 3558, 3566, 3575, 3583, 3592, 3600, 3609, 3617, 3625, 3633, 3641, 3649, 3657, 3665, 3673, 3681, 3689, 3696, 3704, 3711, 3719, 3726, 3734, 3741, 3748, 3755, 3762, 3769, 3776, 3783, 3790, 3797, 3803, 3810, 3816, 3823, 3829, 3836, 3842, 3848, 3854, 3860, 3866, 3872, 3878, 3883, 3889, 3895, 3900, 3906, 3911, 3916, 3921, 3927, 3932, 3937, 3942, 3946, 3951, 3956, 3961, 3965, 3970, 3974, 3978, 3983, 3987, 3991, 3995, 3999, 4003, 4006, 4010, 4014, 4017, 4021, 4024, 4027, 4031, 4034, 4037, 4040, 4043, 4046, 4048, 4051, 4054, 4056, 4059, 4061, 4063, 4066, 4068, 4070, 4072, 4074, 4075, 4077, 4079, 4080, 4082, 4083, 4085, 4086, 4087, 4088, 4089, 4090, 4091, 4092, 4092, 4093, 4094, 4094, 4094, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4094, 4094, 4094, 4093, 4092, 4092, 4091, 4090, 4089, 4088, 4087, 4086, 4085, 4083, 4082, 4080, 4079, 4077, 4075, 4074, 4072, 4070, 4068, 4066, 4063, 4061, 4059, 4056, 4054, 4051, 4048, 4046, 4043, 4040, 4037, 4034, 4031, 4027, 4024, 4021, 4017, 4014, 4010, 4006, 4003, 3999, 3995, 3991, 3987, 3983, 3978, 3974, 3970, 3965, 3961, 3956, 3951, 3946, 3942, 3937, 3932, 3927, 3921, 3916, 3911, 3906, 3900, 3895, 3889, 3883, 3878, 3872, 3866, 3860, 3854, 3848, 3842, 3836, 3829, 3823, 3816, 3810, 3803, 3797, 3790, 3783, 3776, 3769, 3762, 3755, 3748, 3741, 3734, 3726, 3719, 3711, 3704, 3696, 3689, 3681, 3673, 3665, 3657, 3649, 3641, 3633, 3625, 3617, 3609, 3600, 3592, 3583, 3575, 3566, 3558, 3549, 3540, 3531, 3522, 3513, 3504, 3495, 3486, 3477, 3468, 3458, 3449, 3440, 3430, 3421, 3411, 3402, 3392, 3382, 3372, 3363, 3353, 3343, 3333, 3323, 3313, 3302, 3292, 3282, 3272, 3261, 3251, 3241, 3230, 3220, 3209, 3198, 3188, 3177, 3166, 3155, 3145, 3134, 3123, 3112, 3101, 3090, 3079, 3068, 3056, 3045, 3034, 3023, 3011, 3000, 2988, 2977, 2966, 2954, 2942, 2931, 2919, 2908, 2896, 2884, 2872, 2861, 2849, 2837, 2825, 2813, 2801, 2789, 2777, 2765, 2753, 2741, 2729, 2717, 2705, 2692, 2680, 2668, 2656, 2643, 2631, 2619, 2606, 2594, 2582, 2569, 2557, 2544, 2532, 2519, 2507, 2494, 2482, 2469, 2456, 2444, 2431, 2419, 2406, 2393, 2380, 2368, 2355, 2342, 2330, 2317, 2304, 2291, 2279, 2266, 2253, 2240, 2227, 2215, 2202, 2189, 2176, 2163, 2150, 2138, 2125, 2112, 2099, 2086, 2073, 2060, 2048, 2035, 2022, 2009, 1996, 1983, 1970, 1957, 1945, 1932, 1919, 1906, 1893, 1880, 1868, 1855, 1842, 1829, 1816, 1804, 1791, 1778, 1765, 1753, 1740, 1727, 1715, 1702, 1689, 1676, 1664, 1651, 1639, 1626, 1613, 1601, 1588, 1576, 1563, 1551, 1538, 1526, 1513, 1501, 1489, 1476, 1464, 1452, 1439, 1427, 1415, 1403, 1390, 1378, 1366, 1354, 1342, 1330, 1318, 1306, 1294, 1282, 1270, 1258, 1246, 1234, 1223, 1211, 1199, 1187, 1176, 1164, 1153, 1141, 1129, 1118, 1107, 1095, 1084, 1072, 1061, 1050, 1039, 1027, 1016, 1005, 994, 983, 972, 961, 950, 940, 929, 918, 907, 897, 886, 875, 865, 854, 844, 834, 823, 813, 803, 793, 782, 772, 762, 752, 742, 732, 723, 713, 703, 693, 684, 674, 665, 655, 646, 637, 627, 618, 609, 600, 591, 582, 573, 564, 555, 546, 537, 529, 520, 512, 503, 495, 486, 478, 470, 462, 454, 446, 438, 430, 422, 414, 406, 399, 391, 384, 376, 369, 361, 354, 347, 340, 333, 326, 319, 312, 305, 298, 292, 285, 279, 272, 266, 259, 253, 247, 241, 235, 229, 223, 217, 212, 206, 200, 195, 189, 184, 179, 174, 168, 163, 158, 153, 149, 144, 139, 134, 130, 125, 121, 117, 112, 108, 104, 100, 96, 92, 89, 85, 81, 78, 74, 71, 68, 64, 61, 58, 55, 52, 49, 47, 44, 41, 39, 36, 34, 32, 29, 27, 25, 23, 21, 20, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 20, 21, 23, 25, 27, 29, 32, 34, 36, 39, 41, 44, 47, 49, 52, 55, 58, 61, 64, 68, 71, 74, 78, 81, 85, 89, 92, 96, 100, 104, 108, 112, 117, 121, 125, 130, 134, 139, 144, 149, 153, 158, 163, 168, 174, 179, 184, 189, 195, 200, 206, 212, 217, 223, 229, 235, 241, 247, 253, 259, 266, 272, 279, 285, 292, 298, 305, 312, 319, 326, 333, 340, 347, 354, 361, 369, 376, 384, 391, 399, 406, 414, 422, 430, 438, 446, 454, 462, 470, 478, 486, 495, 503, 512, 520, 529, 537, 546, 555, 564, 573, 582, 591, 600, 609, 618, 627, 637, 646, 655, 665, 674, 684, 693, 703, 713, 723, 732, 742, 752, 762, 772, 782, 793, 803, 813, 823, 834, 844, 854, 865, 875, 886, 897, 907, 918, 929, 940, 950, 961, 972, 983, 994, 1005, 1016, 1027, 1039, 1050, 1061, 1072, 1084, 1095, 1107, 1118, 1129, 1141, 1153, 1164, 1176, 1187, 1199, 1211, 1223, 1234, 1246, 1258, 1270, 1282, 1294, 1306, 1318, 1330, 1342, 1354, 1366, 1378, 1390, 1403, 1415, 1427, 1439, 1452, 1464, 1476, 1489, 1501, 1513, 1526, 1538, 1551, 1563, 1576, 1588, 1601, 1613, 1626, 1639, 1651, 1664, 1676, 1689, 1702, 1715, 1727, 1740, 1753, 1765, 1778, 1791, 1804, 1816, 1829, 1842, 1855, 1868, 1880, 1893, 1906, 1919, 1932, 1945, 1957, 1970, 1983, 1996, 2009, 2022, 2035};

// uint32_t sine_lut[500] = {
// 2048, 2073, 2099, 2125, 2150, 2176, 2202, 2227, 2253, 2279, 2304, 2330, 2355, 2380, 2406, 2431, 2456, 2482, 2507, 2532, 2557, 2582, 2606, 2631, 2656, 2680, 2705, 2729, 2753, 2777, 2801, 2825, 2849, 2872, 2896, 2919, 2942, 2966, 2988, 3011, 3034, 3056, 3079, 3101, 3123, 3145, 3166, 3188, 3209, 3230, 3251, 3272, 3292, 3313, 3333, 3353, 3372, 3392, 3411, 3430, 3449, 3468, 3486, 3504, 3522, 3540, 3558, 3575, 3592, 3609, 3625, 3641, 3657, 3673, 3689, 3704, 3719, 3734, 3748, 3762, 3776, 3790, 3803, 3816, 3829, 3842, 3854, 3866, 3878, 3889, 3900, 3911, 3921, 3932, 3942, 3951, 3961, 3970, 3978, 3987, 3995, 4003, 4010, 4017, 4024, 4031, 4037, 4043, 4048, 4054, 4059, 4063, 4068, 4072, 4075, 4079, 4082, 4085, 4087, 4089, 4091, 4092, 4094, 4094, 4095, 4095, 4095, 4094, 4094, 4092, 4091, 4089, 4087, 4085, 4082, 4079, 4075, 4072, 4068, 4063, 4059, 4054, 4048, 4043, 4037, 4031, 4024, 4017, 4010, 4003, 3995, 3987, 3978, 3970, 3961, 3951, 3942, 3932, 3921, 3911, 3900, 3889, 3878, 3866, 3854, 3842, 3829, 3816, 3803, 3790, 3776, 3762, 3748, 3734, 3719, 3704, 3689, 3673, 3657, 3641, 3625, 3609, 3592, 3575, 3558, 3540, 3522, 3504, 3486, 3468, 3449, 3430, 3411, 3392, 3372, 3353, 3333, 3313, 3292, 3272, 3251, 3230, 3209, 3188, 3166, 3145, 3123, 3101, 3079, 3056, 3034, 3011, 2988, 2966, 2942, 2919, 2896, 2872, 2849, 2825, 2801, 2777, 2753, 2729, 2705, 2680, 2656, 2631, 2606, 2582, 2557, 2532, 2507, 2482, 2456, 2431, 2406, 2380, 2355, 2330, 2304, 2279, 2253, 2227, 2202, 2176, 2150, 2125, 2099, 2073, 2048, 2022, 1996, 1970, 1945, 1919, 1893, 1868, 1842, 1816, 1791, 1765, 1740, 1715, 1689, 1664, 1639, 1613, 1588, 1563, 1538, 1513, 1489, 1464, 1439, 1415, 1390, 1366, 1342, 1318, 1294, 1270, 1246, 1223, 1199, 1176, 1153, 1129, 1107, 1084, 1061, 1039, 1016, 994, 972, 950, 929, 907, 886, 865, 844, 823, 803, 782, 762, 742, 723, 703, 684, 665, 646, 627, 609, 591, 573, 555, 537, 520, 503, 486, 470, 454, 438, 422, 406, 391, 376, 361, 347, 333, 319, 305, 292, 279, 266, 253, 241, 229, 217, 206, 195, 184, 174, 163, 153, 144, 134, 125, 117, 108, 100, 92, 85, 78, 71, 64, 58, 52, 47, 41, 36, 32, 27, 23, 20, 16, 13, 10, 8, 6, 4, 3, 1, 1, 0, 0, 0, 1, 1, 3, 4, 6, 8, 10, 13, 16, 20, 23, 27, 32, 36, 41, 47, 52, 58, 64, 71, 78, 85, 92, 100, 108, 117, 125, 134, 144, 153, 163, 174, 184, 195, 206, 217, 229, 241, 253, 266, 279, 292, 305, 319, 333, 347, 361, 376, 391, 406, 422, 438, 454, 470, 486, 503, 520, 537, 555, 573, 591, 609, 627, 646, 665, 684, 703, 723, 742, 762, 782, 803, 823, 844, 865, 886, 907, 929, 950, 972, 994, 1016, 1039, 1061, 1084, 1107, 1129, 1153, 1176, 1199, 1223, 1246, 1270, 1294, 1318, 1342, 1366, 1390, 1415, 1439, 1464, 1489, 1513, 1538, 1563, 1588, 1613, 1639, 1664, 1689, 1715, 1740, 1765, 1791, 1816, 1842, 1868, 1893, 1919, 1945, 1970, 1996, 2022};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USB_Device_Init();
  MX_DAC1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  // uint16_t dac_val = 1024; // Mid-scale value for 12-bit DAC
  // if (HAL_DAC_Start(&hdac1, DAC_CHANNEL_1) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_val);

  HAL_TIM_Base_Start(&htim2);

  // Start DAC with DMA
  if (HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t *)sine_lut, 200, DAC_ALIGN_12B_R) != HAL_OK)
  {
    Error_Handler(); // Check if this is causing issues
  }

  // uint32_t DAC_OUT[4] = {0, 1241, 2482, 3723};
  // uint8_t i = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // uint32_t voltage_mv = (dac_val * 3300) / 4096;
    // printf("DAC Output: %u (%lu.%03lu V)\r\n", dac_val, voltage_mv / 1000, voltage_mv % 1000);
    // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    // printf("Hello from STM32!\r\n");
    // HAL_Delay(1000);

    // for(int i = 0; i < 200; i++)
    // {
    //   HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, sine_lut_full[i]);
    //   HAL_Delay(100); // Adjust delay for frequency control
    // }

    // DAC1->DHR12R1 = sine_lut_full[i++];
    //     if(i == 200)
    //     {
    //         i = 0;
    //     }
    // HAL_Delay(1);
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 25;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief DAC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */

  /** DAC Initialization
   */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
   */
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_AUTOMATIC;
  sConfig.DAC_DMADoubleDataMode = DISABLE;
  sConfig.DAC_SignedFormat = DISABLE;
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_T2_TRGO;
  sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_EXTERNAL;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE; // Changed from TIM_TRGO_ENABLE
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac)
{
  // Toggle LED to show DMA is working
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

int _write(int file, char *ptr, int len)
{

  uint32_t timeout = HAL_GetTick() + 100; // 100ms timeout
  while (HAL_GetTick() < timeout)
  {
    if (CDC_Transmit_FS((uint8_t *)ptr, len) == USBD_OK)
    {
      return len;
    }
    HAL_Delay(1);
  }
  return -1; // Error: USB not ready or timeout
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
