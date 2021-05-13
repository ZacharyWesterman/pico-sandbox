#include "lcd.hpp"

lcd::lcd(i2c_inst_t* i2c_instance, uint i2c_address) noexcept
{
	i2c = i2c_instance;
	address = i2c_address;

	//initialize the display
	send_byte(0x03, LCD_COMMAND);
	send_byte(0x03, LCD_COMMAND);
	send_byte(0x03, LCD_COMMAND);
	send_byte(0x02, LCD_COMMAND);

	send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
	send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
	send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
	clear();
}

void lcd::write_byte(uint8_t val) const noexcept
{
	i2c_write_blocking(i2c, address, &val, 1, false);
}

void lcd::toggle_enable(uint8_t val) const noexcept
{
	const int delay = 600; //microseconds
	sleep_us(delay);
	write_byte(val | LCD_ENABLE_BIT);
	sleep_us(delay);
	write_byte(val & ~LCD_ENABLE_BIT);
	sleep_us(delay);
}

void lcd::send_byte(uint8_t val, int mode) const noexcept
{
	uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
	uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

	write_byte(high);
	toggle_enable(high);
	write_byte(low);
	toggle_enable(low);
}

void lcd::clear(void) const noexcept
{
	send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

void lcd::cursor(int line, int position) const noexcept
{
	int val = line ? (0xC0 + position) : (0x80 + position);
	send_byte(val, LCD_COMMAND);
}

void lcd::character(char val) const noexcept
{
	send_byte(val, LCD_CHARACTER);
}

void lcd::string(const char* const str) const noexcept
{
	int i = 0;
	while (str[i])
	{
		character(str[i++]);
	}
}
