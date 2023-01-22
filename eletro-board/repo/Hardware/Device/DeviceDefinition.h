#ifndef MEDICALHORSE_DEVICE_DEFINITION_H_
#define MEDICALHORSE_DEVICE_DEFINITION_H_

#include <string>

namespace medicalhorse::hardware::device::definition {
enum DeviceType : int8_t { Rele = 0, Motor, Sensor, Timer, HBridge, Pump };

namespace sensor {
enum SensorID : int8_t { THERMOTHERAPY = 0, CRYOTHERAPY, All };
}

namespace temperature {
enum class UNIT { RAW = 0, CELSIUS = 1, FAHRENHEIT = 2 };
}

namespace name {
const std::string rele = "RELE IO Control";
const std::string motor = "MOTOR IO Control";
const std::string sensor = "SENSOR IO control";
const std::string pump = "PUMP IO control";
const std::string timer = "Timer control";
const std::string hbridge = "HBride control";

}  // namespace name

}  // namespace medicalhorse::hardware::device::definition

#endif  // MEDICALHORSE_BOARD_DEFINITION_H_
