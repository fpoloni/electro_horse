

#include "DS1803.h"

#include "../../../eletro-util/repo/StructData/StructData.h"

namespace medicalhorse::hardware::device {

inline int get_celsius(const int raw_value) { return raw_value / 1000; }

inline int get_fahrenheit(const int raw_value) {
  return get_celsius(raw_value) * 9.0 / 5.0 + 32.0;
}

DS1803::DS1803(
    const std::string &name,
    const medicalhorse::hardware::device::definition::temperature::UNIT unit)
    : mDeviceName(name), m_unit(unit), mIndexDevice(0), mCount(0),
      mpOneWireBus(std::make_shared<interface::OneWire>()) {}

bool DS1803::Start() {
  std::vector<std::string> modprobeList;
  int reg = 0;
  int parameter = 0;

  mpOneWireBus->Open();

  mpOneWireBus->Read(reg, &parameter);

  if (parameter <= 1) {
    return false;
  }

  return true;
}

void DS1803::Stop() {}

bool DS1803::GetParameter(int *parameter) {
  if (nullptr != parameter) {
    Temperature(m_unit, 0, parameter);
    return true;
  }

  return false;
}

bool DS1803::SetParameter(const int parameter) {
  mIndexDevice = parameter;
  return true;
}

std::string DS1803::GetName() { return mDeviceName; }

bool DS1803::Temperature(
    const medicalhorse::hardware::device::definition::temperature::UNIT
        measure_unit,
    const int index, int *temperature) {

  int parameter = 0;

  if (index <= mpOneWireBus->Size()) {
    if (mpOneWireBus->Read(index, &parameter)) {

      switch (measure_unit) {
      case medicalhorse::hardware::device::definition::temperature::UNIT::RAW:
        printf("Getting temperature in raw. %d(10) - %.2X(16)\n", parameter,
               parameter);
        break;
      case medicalhorse::hardware::device::definition::temperature::UNIT::
          CELSIUS:
        *temperature = get_celsius(parameter);
        printf("Getting temperature in celsius. %d C\n", *temperature);
        break;
      case medicalhorse::hardware::device::definition::temperature::UNIT::
          FAHRENHEIT:
        *temperature = get_fahrenheit(parameter);
        printf("Getting temperature in fahrenheit. %d F\n", *temperature);
        break;
      }
    }
  }
  return true;
}

} // namespace medicalhorse::hardware::device
