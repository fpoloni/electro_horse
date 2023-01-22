
#include <thread>
#include <math.h>

#include "HBridge.h"
#include "../HBridgeDefinitions.h"

namespace medicalhorse::hardware::device
{
    HBridge::HBridge(const std::string &name) : mDeviceName(name),
                                                mBridgeSide(false),
                                                mIsOpened(false),
                                                mTankPosition(util::thank::position::None),
                                                mpI2C(std::make_unique<interface::I2C>(0x40))
    {
    }

    void HBridge::Test()
    {
        mIsOpened = mpI2C->Open();

        mpI2C->Write(hbridge::Registers::MODE1, 0x00);

        mpI2C->Write(hbridge::Registers::LED0_ON_H, 0x01);
        mpI2C->Write(hbridge::Registers::LED0_ON_L, 0x99);

        mpI2C->Write(hbridge::Registers::LED0_OFF_H, 0x04);
        mpI2C->Write(hbridge::Registers::LED0_OFF_L, 0xcc);


        // Motor control - A
        mpI2C->Write(hbridge::Registers::LED1_ON_H, 0x13);
        mpI2C->Write(hbridge::Registers::LED1_ON_L, 0xFE);

        mpI2C->Write(hbridge::Registers::LED1_OFF_H, 0x00);
        mpI2C->Write(hbridge::Registers::LED1_OFF_L, 0x00);

        // Motor control - B
        mpI2C->Write(hbridge::Registers::LED2_ON_H, 0);
        mpI2C->Write(hbridge::Registers::LED2_ON_L, 0);

        mpI2C->Write(hbridge::Registers::LED2_OFF_H, 0);
        mpI2C->Write(hbridge::Registers::LED2_OFF_L, 0);
    }
    /**
     *  LED0_ON_H = 1h; LED0_ON_L = 99h
        LED on time = 20 % = 819.2 ~ 819 counts.

        Off time = 4CCh (decimal 410 + 819 − 1 = 1228)
        LED0_OFF_H = 4h; LED0_OFF_L = CCh
     *
     */

    bool HBridge::Start()
    {
        mIsOpened = mpI2C->Open();

        mpI2C->Write(hbridge::Registers::MODE1, 0x00);

        (!mBridgeSide) ? ActiveSideA() : ActiveSideB();

        return mIsOpened;
    }

    void HBridge::Stop()
    {
        SetLevel(hbridge::Pins::PWMA, 0);
        SetLevel(hbridge::Pins::PWMB, 0);

        mpI2C->Close();

        mIsOpened = false;

        printf("Debug:%s - Status: %d\n", __FUNCTION__, mIsOpened);
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
        mTankPosition = static_cast<util::thank::position>(parameter);

        if (mIsOpened)
            (!mBridgeSide) ? ActiveSideA() : ActiveSideB();

        return true;
    }

    void HBridge::SetLevel(const int channel, const int value)
    {
        if (!mIsOpened)
        {
            return;
        }

        printf("Debug:%s - Channel %d - Value: %d\n", __FUNCTION__, channel, value);

        (value == 1) ? SetPWM(channel, 0, 4095) : SetPWM(channel, 0, 0);
    }

    void HBridge::PWMFrequency(uint16_t frequency)
    {
        if (!mIsOpened)
        {
            return;
        }

        frequency *= 0.9;
        printf("Debug:%s - Frequency: %d\n", __FUNCTION__, frequency);

        double prescaleval = ((25000000.0/4096.0)/frequency) - 1;
        uint8_t prescale = floor(prescaleval + 0.5);

        // printf("prescale = %d\r\n", prescale);

        int oldmode = 0, newmode = 0;

        mpI2C->Read(hbridge::Registers::MODE1, &oldmode);
        printf("Mode value - OLD content: %d\n", oldmode);

        newmode = (oldmode & 0x7F) | 0x10; // sleep
        printf("Mode value - NEW: %d\n", newmode);

        mpI2C->Write(hbridge::Registers::MODE1, newmode);
        mpI2C->Write(hbridge::Registers::PRESCALE, prescale);
        mpI2C->Write(hbridge::Registers::MODE1, oldmode);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        mpI2C->Write(hbridge::Registers::MODE1, oldmode | 0x80);
    }

    void HBridge::SetDutyCycle(const int channel, const int pulse)
    {
        SetPWM(channel, 0, pulse * (4096 / 100) - 1);
    }

    void HBridge::SetPWM(const int channel, const int state_on, const int state_off)
    {
        printf("Debug:%s - Channel %d, State on/off %d/%d\n", __FUNCTION__, channel, state_on, state_off);

        mpI2C->Write(hbridge::Registers::LED0_ON_L + 4 * (channel), state_on & 0xFF);
        mpI2C->Write(hbridge::Registers::LED0_ON_H + 4 * (channel), state_on >> 8);

        mpI2C->Write(hbridge::Registers::LED0_OFF_L + 4 * (channel), state_off & 0xFF);
        mpI2C->Write(hbridge::Registers::LED0_OFF_H + 4 * (channel), state_off >> 8);
    }

    std::string HBridge::GetName()
    {
        return mDeviceName;
    }

    void HBridge::ActiveSideA()
    {
        PWMFrequency(1000);
        SetDutyCycle(hbridge::Pins::PWMA, 100);
        if (mTankPosition == util::thank::position::CRYOTHERAPY)
        {
            SetLevel(hbridge::Pins::AIN1, 0);
            SetLevel(hbridge::Pins::AIN2, 1);
        }
        else if (mTankPosition == util::thank::position::THERMOTHERAPY)
        {
            SetLevel(hbridge::Pins::AIN1, 1);
            SetLevel(hbridge::Pins::AIN2, 0);
        }
        else
        {
            Stop();
        }
    }

    void HBridge::ActiveSideB()
    {
        PWMFrequency(1000);
        SetDutyCycle(hbridge::Pins::PWMB, 100);
        if (mTankPosition == util::thank::position::CRYOTHERAPY)
        {
            SetLevel(hbridge::Pins::BIN1, 0);
            SetLevel(hbridge::Pins::BIN1, 1);
        }
        else if (mTankPosition == util::thank::position::THERMOTHERAPY)
        {
            SetLevel(hbridge::Pins::BIN1, 1);
            SetLevel(hbridge::Pins::BIN1, 0);
        }
        else
        {
            Stop();
        }
    }

} // namespace medicalhorse::hardware::device
