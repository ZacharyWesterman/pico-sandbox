cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(test
	test.cpp
	soil.cpp
	lcd.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(
	test
	pico_stdlib
	pico_binary_info
	hardware_i2c
)

# Enable USB debug, disable UART debug
pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(test)
