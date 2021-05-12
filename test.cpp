#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#include "soil.hpp"

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
	soil sensor (i2c0);

	int iteration = 0;
	while(true)
	{
		float temperature = sensor.temperature('F');
		int moisture = sensor.moisture();
		printf("[%04d] %d F, %d Capacitive\n", iteration, (int)temperature, moisture);

		sleep_ms(3000);
		iteration += 1;
	}

	return 0;
}
