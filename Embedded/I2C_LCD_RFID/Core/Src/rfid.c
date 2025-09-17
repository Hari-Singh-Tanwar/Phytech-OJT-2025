#include "rfid.h"
#include <stdio.h>

uint8_t card_uid[10];
uint8_t card_uid_length = 0;

SPI_HandleTypeDef SPI;

void RC522_Init(SPI_HandleTypeDef *hspi1) {
    SPI = *hspi1;
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
    if (HAL_SPI_Transmit(&SPI, &addr, 1, 100) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        printf("SPI TX addr err reg 0x%02X\r\n", reg);
        return 0;
    }
    if (HAL_SPI_TransmitReceive(&SPI, &dummy, &rx, 1, 100) != HAL_OK) {
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
    if (HAL_SPI_Transmit(&SPI, &addr, 1, 100) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        printf("SPI TX addr err reg 0x%02X\r\n", reg);
        return;
    }
    if (HAL_SPI_Transmit(&SPI, &value, 1, 100) != HAL_OK) {
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