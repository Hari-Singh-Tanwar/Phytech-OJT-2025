#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"

// Delays are implemented privately in the C file

#define I2C_LCD_MAX	1	// Maximum Number of I2C_LCD Modules in Your Project
#define I2C_LCD_1	0	// I2C_LCD Instance Number 1 (Add more if you need)

/*-----------------------[INTERNAL DEFINITIONS]-----------------------*/
// CMD
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80
// DISPLAY ENTRY
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
// DISPLAY CONTROL
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00
// CURSOR MOTION
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00
// FUNCTION SET
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00
// BACKLIGHT CONTROL
#define LCD_BACKLIGHT           0x08
#define LCD_NOBACKLIGHT         0x00
#define EN                      0b00000100  // Enable bit
#define RW                      0b00000010  // Read/Write bit
#define RS                      0b00000001  // Register select bit

//-----[ Prototypes For All User External Functions ]-----

// Configuration structure and API
typedef struct
{
	I2C_HandleTypeDef* I2C_Handle;
	uint8_t I2C_LCD_Address;
	uint8_t I2C_LCD_nRow; // number of display rows (e.g., 2)
} I2C_LCD_CfgParam_t;

void I2C_LCD_Config(uint8_t I2C_LCD_InstanceIndex, I2C_HandleTypeDef* hi2c, uint8_t address7bit, uint8_t num_rows);

void I2C_LCD_Init(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Clear(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Home(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_SetCursor(uint8_t I2C_LCD_InstanceIndex, uint8_t Col, uint8_t Row);
void I2C_LCD_WriteChar(uint8_t I2C_LCD_InstanceIndex, char Ch);
void I2C_LCD_WriteString(uint8_t I2C_LCD_InstanceIndex, char* Str);

void I2C_LCD_ShiftLeft(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_ShiftRight(uint8_t I2C_LCD_InstanceIndex);

void I2C_LCD_Backlight(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoBacklight(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Display(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoDisplay(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Cursor(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoCursor(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Blink(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoBlink(uint8_t I2C_LCD_InstanceIndex);

void I2C_LCD_CreateCustomChar(uint8_t I2C_LCD_InstanceIndex, uint8_t CharIndex, const uint8_t* CharMap);
void I2C_LCD_PrintCustomChar(uint8_t I2C_LCD_InstanceIndex, uint8_t CharIndex);

#endif /* I2C_LCD_H_ */
