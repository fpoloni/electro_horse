#include "DeviceControl.h"
#include "Device/DeviceDefinition.h"
#include "Device/HBridge/IO/HBridge.h"
#include "Device/Motor/Motor.h"
#include "Device/Reles/Rele.h"
#include "Device/Sensor/DS1803.h"
#include "Device/Sensor/MAX6675.h"
#include "Device/Timer/Timer.h"

namespace medicalhorse {
namespace hardware {
namespace device {

std::shared_ptr<IDevices>
DeviceControl::Create(const definition::DeviceType &deviceType) {
  std::shared_ptr<IDevices> pDevice = nullptr;

  switch (deviceType) {
  case definition::DeviceType::Motor:
    pDevice = std::make_shared<Motor>(definition::name::motor);
    break;
  case definition::DeviceType::Rele:
    pDevice = std::make_shared<Rele>(definition::name::rele);
    break;
  case definition::DeviceType::Sensor:
    pDevice = std::make_shared<DS1803>(
        definition::name::sensor,
        medicalhorse::hardware::device::definition::temperature::UNIT::CELSIUS);
    break;
  case definition::DeviceType::Timer:
    pDevice = std::make_shared<Timer>(definition::name::timer);
    break;
  case definition::DeviceType::HBridge:
    pDevice = std::make_shared<iocontrol::HBridge>(definition::name::hbridge);
    break;
  case definition::DeviceType::Pump:
    break;
  default:
    break;
  }

  return pDevice;
}

} // namespace device
} // namespace hardware
} // namespace medicalhorse