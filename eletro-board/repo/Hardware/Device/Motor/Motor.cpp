

#include <iostream>

#include "Motor.h"
#include "Interface/IO/IODefinition.h"
#include "Interface/IO/GPIO.h"

namespace medicalhorse::hardware::device
{

    Motor::Motor(const std::string &name) : mDeviceName(name),
                                            mMotorState(util::motor::OFF),
                                            mpPWMSignal(new interface::PWM(1000))
    {
        interface::GPIO::Add(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_1),
                             static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

        interface::GPIO::Add(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_2),
                             static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

        interface::GPIO::Add(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::PWM_1),
                             static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

        interface::GPIO::Add(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::PWM_2),
                             static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

        // The motors will move to only unique direction
        SetDirection(2);
    }

    bool Motor::Start()
    {
        // The motors will move to only unique direction
        SetDirection(0);
        mpPWMSignal->Start();

        return true;
    }

    void Motor::Stop()
    {
        SetDirection(2);
        mpPWMSignal->SetDutyCycle(interface::pwmdefinition::Level::NONE);
        mpPWMSignal->Enable(false);
        mpPWMSignal->Stop();
    }

    bool Motor::SetParameter(const int parameter)
    {
        switch (parameter)
        {
        case 1:
            mpPWMSignal->SetDutyCycle(hardware::interface::pwmdefinition::Level::SOFT);
            mpPWMSignal->Enable(true);
            printf("PWM level equal SOFT\n");
            break;
        case 2:
            mpPWMSignal->SetDutyCycle(hardware::interface::pwmdefinition::Level::MEDIUM);
            mpPWMSignal->Enable(true);
            printf("PWM level equal MEDIUM\n");

            break;
        case 3:
            mpPWMSignal->SetDutyCycle(hardware::interface::pwmdefinition::Level::HARD);
            mpPWMSignal->Enable(true);
            printf("PWM level equal HARD\n");

            break;
        default:
            mpPWMSignal->Enable(false);
            break;
        }

        return true;
    }

    bool Motor::GetParameter(int *parameter)
    {
        if(nullptr != parameter)
        {
            *parameter = mpPWMSignal->GetDutyCycle();
        }

        return false;
    }

    void Motor::SetDirection(const int direction)
    {
        switch (direction)
        {
        case 0:
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_1),
                                 static_cast<int>(hardware::iodefinition::VALUE::HIGH));
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_2),
                                 static_cast<int>(hardware::iodefinition::VALUE::LOW));
            break;

        case 1:
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_1),
                                 static_cast<int>(hardware::iodefinition::VALUE::LOW));
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_2),
                                 static_cast<int>(hardware::iodefinition::VALUE::HIGH));
            break;

        case 2:
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_1),
                                 static_cast<int>(hardware::iodefinition::VALUE::LOW));
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::MASSAGEMOTOR::DIRECTION_2),
                                 static_cast<int>(hardware::iodefinition::VALUE::LOW));
            break;

        default:
            break;
        }
    }

    std::string Motor::GetName()
    {
        return mDeviceName;
    }

} // namespace medicalhorse::hardware::device
