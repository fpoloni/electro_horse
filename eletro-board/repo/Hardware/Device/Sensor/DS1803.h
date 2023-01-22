

#ifndef MEDICALHORSE_DS1803_H_
#define MEDICALHORSE_DS1803_H_

#include <memory>
#include <string>

#include "Device/DeviceDefinition.h"
#include "Device/IDevices.h"
#include "Interface/SerialBus/1Wire/OneWire.h"

namespace medicalhorse::hardware::device {
class DS1803 : public IDevices {
public:
  DS1803(
      const std::string &name,
      const medicalhorse::hardware::device::definition::temperature::UNIT unit);

  virtual ~DS1803() = default;

  bool Start() override;
  void Stop() override;
  bool SetParameter(const int parameter) override;
  bool GetParameter(int *parameter) override;
  std::string GetName() override;

private:
  bool Temperature(
      const medicalhorse::hardware::device::definition::temperature::UNIT
          measure_unit,
      const int index, int *temperature);

private:
  std::shared_ptr<interface::OneWire> mpOneWireBus;
  std::string mDeviceName;
  medicalhorse::hardware::device::definition::temperature::UNIT m_unit;
  int mIndexDevice;
  int mCount;
};

} // namespace medicalhorse::hardware::device

#endif // MEDICALHORSE_DS1803_H_
