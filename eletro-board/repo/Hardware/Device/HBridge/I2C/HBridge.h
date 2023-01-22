
#ifndef MEDICALHORSE_I2C_HBRIDGE_H_
#define MEDICALHORSE_I2C_HBRIDGE_H_

#include <vector>
#include <string>
#include <memory>

#include "Common.h"
#include "Device/IDevices.h"
#include "Device/DeviceDefinition.h"
#include "Interface/SerialBus/I2C/I2C.h"


namespace medicalhorse::hardware::device
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

        bool Start() override;
        void Stop() override;
        bool SetParameter(const int parameter) override;
        bool GetParameter(int *parameter) override;
        std::string GetName() override;

        void Test();

    private:
        void PWMFrequency(uint16_t frequency);
        void SetDutyCycle(const int channel, const int pulse);
        void SetPWM(const int channel, const int state_on, const int state_off);
        void SetLevel(const int channel, const int value);
        void ActiveSideA();
        void ActiveSideB();

    private:
        bool mBridgeSide;
        bool mIsOpened;
        std::string mDeviceName;
        std::unique_ptr<interface::I2C> mpI2C;
        util::thank::position mTankPosition;
    };

} // namespace medicalhorse::hardware::device

#endif // MEDICALHORSE_HBRIDGE_H