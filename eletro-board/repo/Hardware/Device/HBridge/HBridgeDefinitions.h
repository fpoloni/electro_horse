#ifndef MEDICALHORSE_HBRIDGE_REGISTERS_H_
#define MEDICALHORSE_HBRIDGE_REGISTERS_H_

#include <cinttypes>

namespace medicalhorse::hardware::device::hbridge
{
    enum Registers : uint8_t
    {
        MODE1           = 0x00,
        SUBADR1         = 0x02,
        SUBADR2         = 0x03,
        SUBADR3         = 0x04,
        PRESCALE        = 0xFE,

        LED0_ON_L       = 0x06,
        LED0_ON_H       = 0x07,
        LED0_OFF_L      = 0x08,
        LED0_OFF_H      = 0x09,

        LED1_ON_L       = 0x0A,
        LED1_ON_H       = 0x0B,
        LED1_OFF_L      = 0x0C,
        LED1_OFF_H      = 0x0D,

        LED2_ON_L       = 0x0E,
        LED2_ON_H       = 0x0F,
        LED2_OFF_L      = 0x10,
        LED2_OFF_H      = 0x11,

        ALLLED_ON_L     = 0xFA,
        ALLLED_ON_H     = 0xFB,
        ALLLED_OFF_L    = 0xFC,
        ALLLED_OFF_H    = 0xFD
    };

    enum Pins : uint8_t
    {
        PWMA = 0,
        AIN1 = 1,
        AIN2 = 2,
        PWMB = 5,
        BIN1 = 3,
        BIN2 = 4
    };

    enum PwmState : uint8_t
    {
        ON = 0x00,
        OFF = 0x01
    };

} // namespace medicalhorse::hardware::device::hbridge

#endif // MEDICALHORSE_HBRIDGE_REGISTERS_H_