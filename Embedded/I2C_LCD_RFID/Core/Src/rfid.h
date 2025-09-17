#ifndef __RFID_H
#define __RFID_H

#include "main.h"

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


// Function Prototypes
void RC522_Init(SPI_HandleTypeDef *hspi1);
uint8_t RC522_Read_Register(uint8_t reg);
void RC522_Write_Register(uint8_t reg, uint8_t value);
void RC522_Reset(void);
uint8_t RC522_Request(uint8_t req_mode, uint8_t* tag_type);
uint8_t RC522_Anticoll(uint8_t* serial_num);
uint8_t RC522_Communicate_With_Card(uint8_t command, uint8_t* send_data, uint8_t send_len, uint8_t* back_data, uint16_t* back_len);
uint8_t RC522_Check_Card(void);
#endif