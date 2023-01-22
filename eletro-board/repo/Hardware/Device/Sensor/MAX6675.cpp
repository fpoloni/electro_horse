
#include "MAX6675.h"

#define SIGNAL_VALUE 0x80000000
#define VALID_READ 0x0004

inline int get_celsius(const int raw_value) { return raw_value * 0.25; }

inline int get_fahrenheit(const int raw_value) {
  return get_celsius(raw_value) * 9.0 / 5.0 + 32.0;
}

inline bool get_signal(const int raw_value) {
  return (SIGNAL_VALUE & raw_value);
}

namespace medicalhorse::hardware::device {

MAX6675::MAX6675(
    const std::string DeviveName, const iodefinition::SENSOR_SPI Channel,
    const medicalhorse::hardware::device::definition::temperature::UNIT unit)
    : m_device_name(DeviveName), m_channel(Channel), m_unit(unit) {}

bool MAX6675::Start() {
  mp_spi = std::make_unique<medicalhorse::hardware::interface::Spi>(
      iodefinition::SENSOR_SPI::CH0);
  bool ret = mp_spi->Open();
  return ret;
}
void MAX6675::Stop() { mp_spi->Close(); }

bool MAX6675::GetParameter(int *parameter) {
  bool ret = false;
  if (nullptr != parameter) {
    ret = Temperature(m_unit, parameter);
  }

  return ret;
}

bool MAX6675::SetParameter(const int parameter) { return true; }

bool MAX6675::Temperature(
    medicalhorse::hardware::device::definition::temperature::UNIT measure_unit,
    int *temperature) {
  std::vector<char> package(PACKAGE_SIZE);
  int16_t raw_sensor_value = 0, raw_temperature_value = 0;

  mp_spi->Read(PACKAGE_SIZE, (int *)package.data());
  raw_sensor_value = (((package[0] << 8) | package[1]));
  raw_temperature_value = (raw_sensor_value >> 3);

  printf("Debug %.2X(16)\n", raw_sensor_value);

  if (get_signal(raw_sensor_value)) {
    raw_temperature_value = ~raw_temperature_value;
    printf("Negative value: %d\n", raw_temperature_value);
  }

  switch (measure_unit) {
  case medicalhorse::hardware::device::definition::temperature::UNIT::RAW:
    printf("Getting temperature in raw. %d(10) - %.2X(16)\n",
           raw_temperature_value, raw_temperature_value);
    break;
  case medicalhorse::hardware::device::definition::temperature::UNIT::CELSIUS:
    *temperature = get_celsius(raw_temperature_value);
    printf("Getting temperature in celsius. %d C\n", *temperature);
    break;
  case medicalhorse::hardware::device::definition::temperature::UNIT::
      FAHRENHEIT:
    *temperature = get_fahrenheit(raw_temperature_value);
    printf("Getting temperature in fahrenheit. %d F\n", *temperature);
    break;
  }

  return true;
}

std::string MAX6675::GetName() { return m_device_name; }
} // namespace medicalhorse::hardware::device