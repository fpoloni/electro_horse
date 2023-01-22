
#ifndef MEDICALHORSE_IO_HBRIDGE_H_
#define MEDICALHORSE_IO_HBRIDGE_H_

#include <vector>
#include <string>
#include <memory>

#include "Common.h"
#include "Device/IDevices.h"
#include "Device/DeviceDefinition.h"

namespace medicalhorse::hardware::device::iocontrol
{
    class HBridge : public IDevices
    {
    public:
        /**
         * @brief Constructor
         */
        HBridge(const std::string &name);

        /**
         * @brief Desctructor
         */
        virtual ~HBridge() = default;

        /**
         * @brief
         */
        bool Start() override;

        /**
         * @brief
         */
        void Stop() override;

        /**
         * @brief
         */
        bool SetParameter(const int parameter) override;

        /**
         * @brief
         */
        bool GetParameter(int *parameter) override;

        /**
         * @brief
         */
        std::string GetName() override;

    private:
        void SelectTank(const util::thank::position position, const bool mode);

        std::string mDeviceName;
        int mTankPosition;
    };

} // namespace medicalhorse::hardware::device

#endif // MEDICALHORSE_HBRIDGE_H