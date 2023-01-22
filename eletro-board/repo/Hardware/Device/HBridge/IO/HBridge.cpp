
#include <thread>
#include <math.h>

#include "Interface/IO/IODefinition.h"
#include "Interface/IO/GPIO.h"

#include "HBridge.h"
#include "../HBridgeDefinitions.h"

namespace medicalhorse::hardware::device::iocontrol
{
    HBridge::HBridge(const std::string &name) : mDeviceName(name),
                                                mTankPosition(static_cast<int>(util::thank::position::None))

    {
    }

    bool HBridge::Start()
    {
        printf("Debug:%s \n", __FUNCTION__);

        interface::GPIO::Add(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_THERM),
                             static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

        interface::GPIO::Add(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_CRYO),
                             static_cast<int>(hardware::iodefinition::DIRECTION::OUTPUT));

        interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_THERM),
                             static_cast<int>(hardware::iodefinition::VALUE::HIGH));

        interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_CRYO),
                             static_cast<int>(hardware::iodefinition::VALUE::HIGH));

        return true;
    }

    void HBridge::Stop()
    {
        printf("Debug:%s \n", __FUNCTION__);

        interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_THERM),
                             static_cast<int>(hardware::iodefinition::VALUE::HIGH));

        interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_CRYO),
                             static_cast<int>(hardware::iodefinition::VALUE::HIGH));
    }

    bool HBridge::GetParameter(int *parameter)
    {
        bool retVal = false;

        if (nullptr != parameter)
        {
            retVal = true;
            *parameter = static_cast<int>(mTankPosition);
        }
        return retVal;
    }

    bool HBridge::SetParameter(const int parameter)
    {
        // Choose the valvule position
        mTankPosition = parameter;
        
        this->SelectTank(static_cast<util::thank::position>(parameter), true);

        return true;
    }

    std::string HBridge::GetName()
    {
        return mDeviceName;
    }

    void HBridge::SelectTank(const util::thank::position position, const bool mode)
    {
        switch(position)
        {
        case util::thank::position::CRYOTHERAPY:
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_CRYO),
                                 static_cast<int>(hardware::iodefinition::VALUE::LOW));
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_THERM),
                                 static_cast<int>(hardware::iodefinition::VALUE::HIGH));

            if (mode)
            {
                printf("Waiting for tank selection - CRYO - 5 seconds.\n");
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }

            break;
        case util::thank::position::THERMOTHERAPY:
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_CRYO),
                                 static_cast<int>(hardware::iodefinition::VALUE::HIGH));
            interface::GPIO::Set(static_cast<int>(hardware::iodefinition::TANKSELECTOR::TANK_THERM),
                                 static_cast<int>(hardware::iodefinition::VALUE::LOW));
            
            if (mode)
            {
                printf("Waiting for tank selection - THERMO - 5 seconds.\n");
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }

            break;
        }

        Stop();

    }
} // namespace medicalhorse::hardware::device::iocontrol
