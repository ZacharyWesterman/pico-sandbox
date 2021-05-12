#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define SOIL_ADDRESS 0x36

void setup_i2c(i2c_inst_t* i2c, uint sda, uint scl)
{
	i2c_init(i2c, 115200);
	gpio_set_function(sda, GPIO_FUNC_I2C);
	gpio_set_function(scl, GPIO_FUNC_I2C);
	gpio_pull_up(sda);
	gpio_pull_up(scl);
	bi_decl(bi_2pins_with_func(sda, scl, GPIO_FUNC_I2C));
}

//Get temperature (in degrees Celcius)
float get_temp(i2c_inst_t* i2c, uint address)
{
	//Request temperature
	const uint8_t txdata[2] = { 0x00, 0x04 };
	i2c_write_blocking(i2c, address, txdata, 2, false);

	sleep_ms(1);//wait a little bit for response.

	//Read temperature
	uint8_t rxdata[4];
	i2c_read_blocking(i2c, address, rxdata, 4, false);

	//Convert to Celcius
	int32_t tempdata = ((int32_t)rxdata[0] << 24) | ((int32_t)rxdata[1] << 16) | ((int32_t)rxdata[2] << 8) | (int32_t)rxdata[3];
	return (1.0f / (1UL << 16)) * tempdata;
}

//Get moisture value (range from 0 to 1023)
//A good moisture for plants might be 200 to 300
uint16_t get_moisture(i2c_inst_t* i2c, uint address)
{
	//Request moisture measurement
	const uint8_t txdata[2] = { 0x0F, 0x10 };
	i2c_write_blocking(i2c, address, txdata, 2, false);

	sleep_ms(10); //delay to allow sampling

	//Read moisture measurement
	uint8_t rxdata[2];
	i2c_read_blocking(i2c, address, rxdata, 2, false);

	return ((uint16_t)rxdata[0] << 8) | (uint16_t)rxdata[1];
}

int main() {
	stdio_init_all();

	setup_i2c(i2c0, 4, 5);

	int iter = 0;
	while(true)
	{
		float celcius = get_temp(i2c0, SOIL_ADDRESS);
		int moisture = get_moisture(i2c0, SOIL_ADDRESS);
		printf("[%04d] %d F, %d Capacitive\n", iter, (int)(celcius * 1.8) + 32, moisture);

		sleep_ms(3000);
		iter += 1;
	}

	return 0;
}
