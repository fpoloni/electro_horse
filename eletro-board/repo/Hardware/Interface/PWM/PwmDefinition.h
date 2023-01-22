/**
 * @author Fabricio Poloni
 * PWM signals for modulation control
 *
 * At the moment had been used commercial module to
 * achieve the project goals.
 */

#ifndef MEDICALHORSE_PWMSIGNAL_DEFINITION_H_
#define MEDICALHORSE_PWMSIGNAL_DEFINITION_H_

namespace medicalhorse::hardware::interface::pwmdefinition
{

    /**
 * @brief Enum to define the PWM mode during the use
 * that maybe just plot the values in the screen or
 * pin io control.
 *
 */
    enum Mode : uint8_t
    {
        STUB = 0,
        REAL = 1,
        UNDEFINED = 2
    };

    /**
 * @brief Enum to define the dutycyle level regarding to
 * pin io control
 */
    enum Level : uint8_t
    {
        NONE = 0,
        SOFT = 25,
        MEDIUM = 50,
        HARD = 75
    };

    enum PinState : uint8_t
    {
        HIGH = 1,
        LOW = 0
    };

    typedef struct
    {
        int timeH;
        int timeL;
        int frequency;

    } PWMValues_t;

} // namespace medicalhorse::hardware::interface::pwmdefinition

#endif // MEDICALHORSE_PWMSIGNAL_DEFINITION_H_