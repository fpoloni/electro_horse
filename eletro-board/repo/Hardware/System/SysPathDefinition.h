

#ifndef MEDICALHORSE_SYSPATH_DEFINITION_H_
#define MEDICALHORSE_SYSPATH_DEFINITION_H_

#include <string>

namespace medicalhorse {
namespace hardware {
namespace sysclassdefinition {

/**
 * @brief Constant string path to indicate the available
 * serial bus interfaces.
 */
namespace serialbus {
const std::string onewire = "/sys/bus/w1/devices/";
const std::string i2c = "/dev/i2c-";
const std::string spi = "/dev/spidev";

namespace spi_id {
const std::string ch_0 = "0.0";
const std::string ch_1 = "0.1";
} // namespace spi_id

/**
 * @brief The substring expected in the sensor module
 * @param  28-00000 is the substring.
 */
namespace sbtsensor {
const std::string keyword = "28";
}
} // namespace serialbus

/**
 * @brief Constant string path to indicate the content
 * gpio available
 */
namespace sysclass {
const std::string gpio = "/sys/class/gpio";
}

} // namespace sysclassdefinition
} // namespace hardware
} // namespace medicalhorse

#endif // MEDICALHORSE_SYSPATH_DEFINITION_H_
