/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * STM32 Nucleo F446RE - RFID Card Reader with UART Serial Output
  * Components:
  * - STM32 Nucleo F446RE
  * - RC522 RFID Reader (I2C mode, address 0x28)
  * 
  * Connections:
  * I2C1 (PB8 - SCL, PB9 - SDA):
  * - RC522: VCC->3.3V, GND->GND, SDA->PB9, SCL->PB8, RST->PC7
  * UART2 (PA2 - TX, PA3 - RX): USB Serial for debugging
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// RC522 I2C address
#define RC522_I2C_ADDR      0x28 << 1  // RC522 I2C mode address

// RC522 Registers
#define RC522_REG_COMMAND       0x01
#define RC522_REG_COM_I_EN      0x02
#define RC522_REG_DIV_I_EN      0x03
#define RC522_REG_COM_IRQ       0x04
#define RC522_REG_DIV_IRQ       0x05
#define RC522_REG_ERROR         0x06
#define RC522_REG_STATUS1       0x07
#define RC522_REG_STATUS2       0x08
#define RC522_REG_FIFO_DATA     0x09
#define RC522_REG_FIFO_LEVEL    0x0A
#define RC522_REG_WATER_LEVEL   0x0B
#define RC522_REG_CONTROL       0x0C
#define RC522_REG_BIT_FRAMING   0x0D
#define RC522_REG_COLL          0x0E
#define RC522_REG_MODE          0x11
#define RC522_REG_TX_MODE       0x12
#define RC522_REG_RX_MODE       0x13
#define RC522_REG_TX_CONTROL    0x14
#define RC522_REG_TX_ASK        0x15
#define RC522_REG_TX_SEL        0x16
#define RC522_REG_RX_SEL        0x17
#define RC522_REG_RX_THRESHOLD  0x18
#define RC522_REG_DEMOD         0x19
#define RC522_REG_MF_TX         0x1C
#define RC522_REG_MF_RX         0x1D
#define RC522_REG_SERIAL_SPEED  0x1F
#define RC522_REG_CRC_RESULT_H  0x21
#define RC522_REG_CRC_RESULT_L  0x22
#define RC522_REG_MOD_WIDTH     0x24
#define RC522_REG_RF_CFG        0x26
#define RC522_REG_GSN           0x27
#define RC522_REG_CW_GSP        0x28
#define RC522_REG_MOD_GSP       0x29
#define RC522_REG_T_MODE        0x2A
#define RC522_REG_T_PRESCALER   0x2B
#define RC522_REG_T_RELOAD_H    0x2C
#define RC522_REG_T_RELOAD_L    0x2D
#define RC522_REG_T_COUNTER_VAL_H 0x2E
#define RC522_REG_T_COUNTER_VAL_L 0x2F
#define RC522_REG_TEST_SEL1     0x31
#define RC522_REG_TEST_SEL2     0x32
#define RC522_REG_TEST_PIN_EN   0x33
#define RC522_REG_TEST_PIN_VALUE 0x34
#define RC522_REG_TEST_BUS      0x35
#define RC522_REG_AUTO_TEST     0x36
#define RC522_REG_VERSION       0x37
#define RC522_REG_ANALOG_TEST   0x38
#define RC522_REG_TEST_DAC1     0x39
#define RC522_REG_TEST_DAC2     0x3A
#define RC522_REG_TEST_ADC      0x3B

// RC522 Commands
#define RC522_CMD_IDLE          0x00
#define RC522_CMD_MEM           0x01
#define RC522_CMD_GENERATE_RANDOM_ID 0x02
#define RC522_CMD_CALC_CRC      0x03
#define RC522_CMD_TRANSMIT      0x04
#define RC522_CMD_NO_CMD_CHANGE 0x07
#define RC522_CMD_RECEIVE       0x08
#define RC522_CMD_TRANSCEIVE    0x0C
#define RC522_CMD_MF_AUTHENT    0x0E
#define RC522_CMD_SOFT_RESET    0x0F

// MIFARE Commands
#define MIFARE_CMD_REQA         0x26
#define MIFARE_CMD_WUPA         0x52
#define MIFARE_CMD_SEL_CL1      0x93
#define MIFARE_CMD_SEL_CL2      0x95
#define MIFARE_CMD_SEL_CL3      0x97
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t card_uid[10];
uint8_t card_uid_length = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
// RC522 Functions
void RC522_Init(void);
uint8_t RC522_Read_Register(uint8_t reg);
void RC522_Write_Register(uint8_t reg, uint8_t value);
void RC522_Reset(void);
uint8_t RC522_Request(uint8_t req_mode, uint8_t* tag_type);
uint8_t RC522_Anticoll(uint8_t* serial_num);
uint8_t RC522_Communicate_With_Card(uint8_t command, uint8_t* send_data, uint8_t send_len, uint8_t* back_data, uint16_t* back_len);
uint8_t RC522_Check_Card(void);
void Display_Card_Info(void);

// Printf redirection
int __io_putchar(int ch);
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
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  
  // Add RC522 Reset pin configuration (PC7)
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  
  // Configure RC522 CS pin (PB6) and set high (not selected)
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
  
  HAL_Delay(100);
  
  // Initialize RC522 over SPI
  RC522_Init();

  // Read RC522 VERSION register to confirm communication
  uint8_t ver = RC522_Read_Register(RC522_REG_VERSION);
  printf("RC522 VERSION=0x%02X (expect ~0x91/0x92)\r\n", ver);

  // Basic status/antenna diagnostics
  uint8_t tx_ctrl = RC522_Read_Register(RC522_REG_TX_CONTROL);
  uint8_t status1 = RC522_Read_Register(RC522_REG_STATUS1);
  uint8_t status2 = RC522_Read_Register(RC522_REG_STATUS2);
  printf("TX_CONTROL=0x%02X (antenna bits=0x%02X) STATUS1=0x%02X STATUS2=0x%02X\r\n",
         tx_ctrl, (tx_ctrl & 0x03), status1, status2);
  
  printf("STM32 RFID Card Reader Initialized\r\n");
  printf("Waiting for RFID cards...\r\n");
  printf("========================================\r\n");
 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (RC522_Check_Card()) {
        Display_Card_Info();
        HAL_Delay(2000);  // Wait 2 seconds before next scan
        printf("Waiting for next card...\r\n");
    }
    HAL_Delay(500);  // Check for cards every 500ms

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Printf redirection to UART2
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// RC522 Functions
void RC522_Init(void) {
    RC522_Reset();
    HAL_Delay(50);
    
    // Configure RC522
    RC522_Write_Register(RC522_REG_T_MODE, 0x8D);
    RC522_Write_Register(RC522_REG_T_PRESCALER, 0x3E);
    RC522_Write_Register(RC522_REG_T_RELOAD_L, 30);
    RC522_Write_Register(RC522_REG_T_RELOAD_H, 0);
    RC522_Write_Register(RC522_REG_TX_ASK, 0x40);
    RC522_Write_Register(RC522_REG_MODE, 0x3D);
    
    // Turn on antenna
    uint8_t value = RC522_Read_Register(RC522_REG_TX_CONTROL);
    if (!(value & 0x03)) {
        RC522_Write_Register(RC522_REG_TX_CONTROL, value | 0x03);
    }
    
    value = RC522_Read_Register(RC522_REG_TX_CONTROL);
    printf("RC522 initialized, antenna=%s (TX_CONTROL=0x%02X)\r\n", (value & 0x03) ? "ON" : "OFF", value);
}

uint8_t RC522_Read_Register(uint8_t reg) {
    uint8_t addr = ((reg << 1) & 0x7E) | 0x80; // read
    uint8_t rx = 0x00;
    uint8_t dummy = 0x00;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // CS low
    __NOP(); __NOP(); __NOP();
    if (HAL_SPI_Transmit(&hspi1, &addr, 1, 100) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        printf("SPI TX addr err reg 0x%02X\r\n", reg);
        return 0;
    }
    if (HAL_SPI_TransmitReceive(&hspi1, &dummy, &rx, 1, 100) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        printf("SPI TRX data err reg 0x%02X\r\n", reg);
        return 0;
    }
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // CS high
    return rx;
}

void RC522_Write_Register(uint8_t reg, uint8_t value) {
    uint8_t addr = (reg << 1) & 0x7E; // write
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // CS low
    __NOP(); __NOP(); __NOP();
    if (HAL_SPI_Transmit(&hspi1, &addr, 1, 100) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        printf("SPI TX addr err reg 0x%02X\r\n", reg);
        return;
    }
    if (HAL_SPI_Transmit(&hspi1, &value, 1, 100) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        printf("SPI TX data err reg 0x%02X\r\n", reg);
        return;
    }
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // CS high
}

void RC522_Reset(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(50);
    
    RC522_Write_Register(RC522_REG_COMMAND, RC522_CMD_SOFT_RESET);
    HAL_Delay(50);
}

uint8_t RC522_Request(uint8_t req_mode, uint8_t* tag_type) {
    uint8_t status;
    uint16_t back_bits;
    
    RC522_Write_Register(RC522_REG_BIT_FRAMING, 0x07);
    
    tag_type[0] = req_mode;
    status = RC522_Communicate_With_Card(RC522_CMD_TRANSCEIVE, tag_type, 1, tag_type, &back_bits);
    
    if ((status != 0) || (back_bits != 0x10)) {
        status = 1;
    }
    
    return status;
}

uint8_t RC522_Anticoll(uint8_t* serial_num) {
    uint8_t status;
    uint8_t i;
    uint8_t serial_check = 0;
    uint16_t back_bits;
    
    RC522_Write_Register(RC522_REG_BIT_FRAMING, 0x00);
    
    serial_num[0] = MIFARE_CMD_SEL_CL1;
    serial_num[1] = 0x20;
    
    status = RC522_Communicate_With_Card(RC522_CMD_TRANSCEIVE, serial_num, 2, serial_num, &back_bits);
    
    if (status == 0) {
        for (i = 0; i < 4; i++) {
            serial_check ^= serial_num[i];
        }
        if (serial_check != serial_num[i]) {
            status = 1;
        }
    }
    
    return status;
}

uint8_t RC522_Communicate_With_Card(uint8_t command, uint8_t* send_data, uint8_t send_len, uint8_t* back_data, uint16_t* back_len) {
    uint8_t status = 1;
    uint8_t irq_en = 0x00;
    uint8_t wait_irq = 0x00;
    uint8_t last_bits;
    uint8_t n;
    uint16_t i;
    
    switch (command) {
        case RC522_CMD_MF_AUTHENT:
            irq_en = 0x12;
            wait_irq = 0x10;
            break;
        case RC522_CMD_TRANSCEIVE:
            irq_en = 0x77;
            wait_irq = 0x30;
            break;
        default:
            break;
    }
    
    RC522_Write_Register(RC522_REG_COM_I_EN, irq_en | 0x80);
    RC522_Write_Register(RC522_REG_COM_IRQ, 0x7F);
    RC522_Write_Register(RC522_REG_FIFO_LEVEL, 0x80);
    RC522_Write_Register(RC522_REG_COMMAND, RC522_CMD_IDLE);
    
    for (i = 0; i < send_len; i++) {
        RC522_Write_Register(RC522_REG_FIFO_DATA, send_data[i]);
    }
    
    RC522_Write_Register(RC522_REG_COMMAND, command);
    
    if (command == RC522_CMD_TRANSCEIVE) {
        RC522_Write_Register(RC522_REG_BIT_FRAMING, RC522_Read_Register(RC522_REG_BIT_FRAMING) | 0x80);
    }
    
    i = 2000;
    do {
        n = RC522_Read_Register(RC522_REG_COM_IRQ);
        i--;
    } while ((i != 0) && !(n & 0x01) && !(n & wait_irq));
    
    RC522_Write_Register(RC522_REG_BIT_FRAMING, RC522_Read_Register(RC522_REG_BIT_FRAMING) & (~0x80));
    
    if (i != 0) {
        uint8_t err = RC522_Read_Register(RC522_REG_ERROR);
        if (!(err & 0x1B)) {
            status = 0;
            
            if (n & irq_en & 0x01) {
                status = 1;
            }
            
            if (command == RC522_CMD_TRANSCEIVE) {
                n = RC522_Read_Register(RC522_REG_FIFO_LEVEL);
                last_bits = RC522_Read_Register(RC522_REG_CONTROL) & 0x07;
                
                if (last_bits) {
                    *back_len = (n - 1) * 8 + last_bits;
                } else {
                    *back_len = n * 8;
                }
                
                if (n == 0) {
                    n = 1;
                }
                
                if (n > 16) {
                    n = 16;
                }
                
                for (i = 0; i < n; i++) {
                    back_data[i] = RC522_Read_Register(RC522_REG_FIFO_DATA);
                }
            }
        } else {
            status = 1;
            printf("RC522 ERR=0x%02X COM_IRQ=0x%02X FIFO_LVL=0x%02X\r\n",
                   err,
                   RC522_Read_Register(RC522_REG_COM_IRQ),
                   RC522_Read_Register(RC522_REG_FIFO_LEVEL));
        }
    }
    
    return status;
}

uint8_t RC522_Check_Card(void) {
    uint8_t status;
    uint8_t tag_type[2];
    
    status = RC522_Request(MIFARE_CMD_REQA, tag_type);
    if (status == 0) {
        status = RC522_Anticoll(card_uid);
        if (status == 0) {
            card_uid_length = 4; // Standard MIFARE card UID length
            return 1;
        }
    }
    return 0;
}

void Display_Card_Info(void) {
    printf("\r\n========== CARD DETECTED ==========\r\n");
    printf("Card UID: ");
    for (int i = 0; i < card_uid_length; i++) {
        printf("%02X", card_uid[i]);
        if (i < card_uid_length - 1) printf(":");
    }
    printf("\r\nCard UID (Decimal): ");
    for (int i = 0; i < card_uid_length; i++) {
        printf("%d", card_uid[i]);
        if (i < card_uid_length - 1) printf(":");
    }
    printf("\r\n===================================\r\n");
    
    // Blink LED to indicate card detection
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
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