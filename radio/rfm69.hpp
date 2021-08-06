#ifndef RFM69_HPP
#define RFM69_HPP

#include "rfm69_registers.hpp"

namespace radio
{
	class rfm69
	{
	private:

	public:
		rfm69(rfm69_register freq_band, char node_id, char network_id, bool is_rfm69hw = false, int interrupt_pin = 18) noexcept;
	};
}

#endif //RFM69_HPP
