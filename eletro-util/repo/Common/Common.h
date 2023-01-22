#ifndef MEDICALHORSE_COMMON_H_
#define MEDICALHORSE_COMMON_H_

#include <cinttypes>

namespace medicalhorse::util
{
    namespace program
    {
        enum state : int8_t
        {
            TEMP_CRYO_ON,
            TEMP_CRYO_OFF,
            TEMP_THERM_ON,
            TEMP_THERM_OFF,
            PUMP_ON,
            PUMP_OFF,
            ALL
        };
    }

    namespace thank
    {
        enum position : int8_t
        {
            CRYOTHERAPY = 0,
            THERMOTHERAPY,
            None
        };
    }

    namespace motor
    {
        enum state : int8_t
        {
            ON = 0,
            OFF
        };
    }

} // namespace medicalhorse::util

#endif // MEDICALHORSE_COMMOM_H_