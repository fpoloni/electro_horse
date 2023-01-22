
#ifndef MEDICALHORSE_DEVICES_INTERFACE_H_
#define MEDICALHORSE_DEVICES_INTERFACE_H_

#include <string>

namespace medicalhorse {
namespace hardware {
namespace device {

class IDevices {
 public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual bool SetParameter(const int parameter) = 0;
  virtual bool GetParameter(int *parameter) = 0;
  virtual std::string GetName() = 0;
};

}  // namespace device
}  // namespace hardware
}  // namespace medicalhorse

#endif  // MEDICALHORSE_DEVICES_INTERFACE_H_
