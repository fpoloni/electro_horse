
#ifndef MEDICALHORSE_MOTOR_H
#define MEDICALHORSE_MOTOR_H

#include <vector>
#include <string>
#include <utility>

#include "Common.h"
#include "Device/IDevices.h"
#include "Interface/PWM/Pwm.h"

namespace medicalhorse::hardware::device
{
    class Motor : public IDevices
    {
    public:

        /**
         * @brief Constructor
         */
        Motor(const std::string &name);

        /**
         * @brief Desctructor
         */
        virtual ~Motor() = default;

        /**
         * @brief Start motor control
         */
        bool Start() override;

        /**
         * @brief Stop motor control
         */
        void Stop() override;

        /**
         * @brief Get method name
         */
        bool SetParameter(const int parameter) override;

        /**
         * @brief Get method name
         */
        bool GetParameter(int *parameter) override;

        /**
         * @brief Get method name
         */
        std::string GetName() override;

    private:
        std::string mDeviceName;
        std::shared_ptr<interface::PWM> mpPWMSignal;
        util::motor::state mMotorState;

        void SetDirection(const int direction);
    };

} // namespace medicalhorse::hardware::device

#endif // MEDICALHORSE_MOTOR_H