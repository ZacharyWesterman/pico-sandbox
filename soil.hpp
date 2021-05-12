#ifndef SOIL_HPP
#define SOIL_HPP

#include "hardware/i2c.h"

//Adafruit's "Seesaw" I2C capacitive moisture sensor.
class soil
{
private:
	i2c_inst_t* i2c;
	uint address;

public:
	soil(i2c_inst_t* i2c_instance, uint i2c_address = 0x36) noexcept;

	//Get temperature in specific units.
	//Valid degree units are 'C', 'F', 'R', and 'K'. That is,
	//Celcius, Fahrenheit, Rankine, and Kelvin, respectively.
	float temperature(char degrees = 'C') const noexcept;

	//Get moisture value (range from 0 to 1023)
	//Very dry might be around 200 to 300
	uint16_t moisture() const noexcept;
};

#endif //SOIL_HPP
