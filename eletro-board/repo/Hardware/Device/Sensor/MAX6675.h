#ifndef MAX6675_H_
#define MAX6675_H_

#include <memory>
#include <string>

#include "Device/DeviceDefinition.h"
#include "Device/IDevices.h"
#include "Interface/SerialBus/SPI/Spi.h"

#define PACKAGE_SIZE 2

namespace medicalhorse::hardware::device {


class MAX6675 : public IDevices {
public:
  MAX6675(
      const std::string DeviceName, const iodefinition::SENSOR_SPI Channel,
      const medicalhorse::hardware::device::definition::temperature::UNIT unit);

  virtual ~MAX6675() = default;

  bool Start() override;
  void Stop() override;
  bool SetParameter(const int parameter) override;
  bool GetParameter(int *parameter) override;
  std::string GetName() override;

private:
  bool Temperature(
      const medicalhorse::hardware::device::definition::temperature::UNIT
          measure_unit,
      int *temperature);

private:
  std::unique_ptr<interface::Spi> mp_spi;
  std::string m_device_name;
  iodefinition::SENSOR_SPI m_channel;
  medicalhorse::hardware::device::definition::temperature::UNIT m_unit;
};

} // namespace medicalhorse::hardware::device

#endif