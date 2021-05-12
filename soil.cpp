#include "soil.hpp"
#include "pico/stdlib.h"

soil::soil(i2c_inst_t* i2c_instance, uint i2c_address) noexcept
{
	i2c = i2c_instance;
	address = i2c_address;
}

float soil::temperature(char degrees) const noexcept
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
	float temp = (1.0f / (1UL << 16)) * tempdata;

	//Convert to chosen scale.
	//Note "efficiency" doesn't really matter here,
	//since we're already waiting 1ms above.
	if (degrees == 'C') return temp; //Celcius
	if (degrees == 'F') return (temp * 1.8) + 32; //Fahrenheit
	if (degrees == 'R') return temp * 1.8; //Rankine

	return temp + 273; //Default to Kelvin.
}

uint16_t soil::moisture() const noexcept
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
