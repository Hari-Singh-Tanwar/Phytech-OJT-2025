#include "lcd.h"

uint8_t command = 0;
uint8_t function = 0;
uint8_t mode = 0;

void send_to_lcd(char data, int rs)
{
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs); // rs = 1 for data, rs=0 for command

    /* write the data to the respective pin */
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data >> 3) & 0x01));
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data >> 2) & 0x01));
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data >> 1) & 0x01));
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data >> 0) & 0x01));

    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
    HAL_Delay(1);
}

void lcd_send_cmd(char cmd)
{
    char datatosend;

    /* send upper nibble first */
    datatosend = ((cmd >> 4) & 0x0f);
    send_to_lcd(datatosend, 0); // RS must be 0 while sending command

    /* send Lower Nibble */
    datatosend = ((cmd) & 0x0f);

    send_to_lcd(datatosend, 0);
}

void lcd_send_data(char data)
{
    char datatosend;

    /* send higher nibble */
    datatosend = ((data >> 4) & 0x0f);
    send_to_lcd(datatosend, 1); // rs =1 for sending data

    /* send Lower nibble */
    datatosend = ((data) & 0x0f);
    send_to_lcd(datatosend, 1);
}

void lcd_init(void)
{
    // clear(); // clear display
    // 4 bit initialisation
    HAL_Delay(50); // wait for >40ms
    lcd_send_cmd(0x30);
    HAL_Delay(5); // wait for >4.1ms
    lcd_send_cmd(0x30);
    HAL_Delay(1); // wait for >100us
    lcd_send_cmd(0x30);
    HAL_Delay(10);

    function = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS; // 4 bit mode, 2 line, 5x8 dots
    lcd_send_cmd( function);          // send function set command
    HAL_Delay(1);

    command = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF; // display on, cursor off, blink off
    lcd_send_cmd( command);             // send display control command
    
    clear(); // clear display
    home(); // return home
    mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT; // entry mode set, left to right, no shift
    lcd_send_cmd(LCD_ENTRYMODESET | mode);          // send entry mode set command
    lcd_send_cmd(mode);          // send entry mode set command

    
}

void display_on(void)
{
    command |= LCD_DISPLAYON;                   // set display on
    lcd_send_cmd(LCD_DISPLAYCONTROL | command); // send display control command
}

void display_off(void)
{
    command &= ~LCD_DISPLAYON;                  // clear display on
    lcd_send_cmd(LCD_DISPLAYCONTROL | command); // send display control command
}

void clear(void)
{
    lcd_send_cmd(LCD_CLEARDISPLAY); // clear display
    HAL_Delay(2);                   // wait for 2ms
}

void home(void)
{
    lcd_send_cmd(LCD_RETURNHOME); // return home
    HAL_Delay(2);                 // wait for 2ms
}

void set_cursor(int row, int col)
{
    if (row == 0)
    {
        // lcd_send_cmd(LCD_SETDDRAMADDR | (0x80 + col)); // set cursor to first row
        lcd_send_cmd(0x80 + col); // set cursor to first row
    }
    else if (row == 1)
    {
        // lcd_send_cmd(LCD_SETDDRAMADDR | (0xC0 + col)); // set cursor to second row
        lcd_send_cmd(0xC0 + col); // set cursor to second row
    }
}

void no_cursor(void)
{
    command &= ~LCD_CURSORON;                   // clear cursor on
    lcd_send_cmd(LCD_DISPLAYCONTROL | command); // send display control command
}

void cursor(void)
{
    command |= LCD_CURSORON;                    // set cursor on
    lcd_send_cmd(LCD_DISPLAYCONTROL | command); // send display control command
}

void no_blink(void)
{
    command &= ~LCD_BLINKON;                    // clear blink on
    lcd_send_cmd(LCD_DISPLAYCONTROL | command); // send display control command
}

void blink(void)
{
    command |= LCD_BLINKON;                     // set blink on
    lcd_send_cmd(LCD_DISPLAYCONTROL | command); // send display control command
}

void scroll_display_left(void)
{
    lcd_send_cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT); // scroll display left
}

void scroll_display_right(void)
{
    lcd_send_cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT); // scroll display right
}

void left_to_right(void)
{
    mode |= LCD_ENTRYRIGHT;                // set entry mode to left to right
    lcd_send_cmd(LCD_ENTRYMODESET | mode); // send entry mode set command
}

void right_to_left(void)
{
    mode &= ~LCD_ENTRYRIGHT;               // clear entry mode to left to right
    lcd_send_cmd(LCD_ENTRYMODESET | mode); // send entry mode set command
}

void autoscroll(void)
{
    mode |= LCD_ENTRYSHIFTINCREMENT;       // set autoscroll
    lcd_send_cmd(LCD_ENTRYMODESET | mode); // send entry mode set command
}

void no_autoscroll(void)
{
    mode &= ~LCD_ENTRYSHIFTINCREMENT;      // clear autoscroll
    lcd_send_cmd(LCD_ENTRYMODESET | mode); // send entry mode set command
}

void lcd_send_string(char *str)
{
    while (*str)
        lcd_send_data(*str++);
}