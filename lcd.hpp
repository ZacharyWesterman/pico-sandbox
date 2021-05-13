#ifndef LCD_HPP
#define LCD_HPP

#include "hardware/i2c.h"

// commands
const int LCD_CLEARDISPLAY = 0x01;
const int LCD_RETURNHOME = 0x02;
const int LCD_ENTRYMODESET = 0x04;
const int LCD_DISPLAYCONTROL = 0x08;
const int LCD_CURSORSHIFT = 0x10;
const int LCD_FUNCTIONSET = 0x20;
const int LCD_SETCGRAMADDR = 0x40;
const int LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
const int LCD_ENTRYSHIFTINCREMENT = 0x01;
const int LCD_ENTRYLEFT = 0x02;

// flags for display and cursor control
const int LCD_BLINKON = 0x01;
const int LCD_CURSORON = 0x02;
const int LCD_DISPLAYON = 0x04;

// flags for display and cursor shift
const int LCD_MOVERIGHT = 0x04;
const int LCD_DISPLAYMOVE = 0x08;

// flags for function set
const int LCD_5x10DOTS = 0x04;
const int LCD_2LINE = 0x08;
const int LCD_8BITMODE = 0x10;

// flag for backlight control
const int LCD_BACKLIGHT = 0x08;

const int LCD_ENABLE_BIT = 0x04;

// Modes for lcd_send_byte
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

#define MAX_LINES      2
#define MAX_CHARS      16

//I2C LCD screen controller.
class lcd
{
private:
	i2c_inst_t* i2c;
	uint address;

	void write_byte(uint8_t val) const noexcept;
	void toggle_enable(uint8_t val) const noexcept;
	void send_byte(uint8_t val, int mode) const noexcept;

public:
	lcd(i2c_inst_t* i2c_instance, uint i2c_address = 0x27) noexcept;

	void clear(void) const noexcept;
	void cursor(int line, int position) const noexcept;

	void character(char val) const noexcept;
	void string(const char* const str) const noexcept;
};

#endif //LCD_HPP
