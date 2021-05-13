#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#include "soil.hpp"
#include "lcd.hpp"

void setup_i2c(i2c_inst_t* i2c, uint sda, uint scl)
{
	i2c_init(i2c, 115200);
	gpio_set_function(sda, GPIO_FUNC_I2C);
	gpio_set_function(scl, GPIO_FUNC_I2C);
	gpio_pull_up(sda);
	gpio_pull_up(scl);
	bi_decl(bi_2pins_with_func(sda, scl, GPIO_FUNC_I2C));
}

int main() {
	stdio_init_all();

	setup_i2c(i2c0, 4, 5);
	const soil sensor (i2c0);
	const lcd screen (i2c0);

	int iteration = 0;
	char buf[32];

	int lastTemp = -999;
	int lastMoist = -999;

	while(true)
	{
		int temperature = sensor.temperature('F');
		int moisture = sensor.moisture();

		if ((lastTemp != temperature) || (lastMoist != moisture))
		{
			screen.clear();
			screen.cursor(0,0);
			sprintf(buf, "%3d F, %4d Cpc", temperature, moisture);
			screen.string(buf);

			lastTemp = temperature;
			lastMoist = moisture;
		}

		sleep_ms(1000);

		iteration += 1;
	}

	return 0;
}
