
#ifndef MEDICALHORSE_DEVICE_CONTROL_H_
#define MEDICALHORSE_DEVICE_CONTROL_H_

#include <memory>
#include <string>

#include "Device/DeviceDefinition.h"
#include "Device/IDevices.h"

namespace medicalhorse {
namespace hardware {
namespace device {

class DeviceControl
{
    public:
        DeviceControl() = default;

        virtual ~DeviceControl() = default;

        std::shared_ptr<IDevices> Create(const definition::DeviceType &deviceType);

};

}  // namespace device
}  // namespace hardware
}  // namespace medicalhorse

#endif // MEDICALHORSE_BOARD_H_