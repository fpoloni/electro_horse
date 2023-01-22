/**
 * @author Fabricio Poloni
 * Pins definition regarding the hardware project
 *
 * At the moment had been used commercial module to
 * achieve the project goals.
 */

#ifndef MEDICALHORSE_IODEFINITION_H_
#define MEDICALHORSE_IODEFINITION_H_

namespace medicalhorse::hardware::iodefinition {
/**
 * @brief Definition regarding the IO directions
 *
 */
enum class DIRECTION { OUTPUT = 1, INPUT = 0 };

enum class VALUE { HIGH = 0, LOW = 1 };

/**
 * @brief Definition regarding the IO pins identification
 * for devices control during the program execution.
 *
 * The attributed number are about the GPIOxx
 */
namespace rele {
enum class TYPE {
  HEATER = 19, // origin pin gpio 19
  FREEZE = 20, // origin pin gpio 20
  PUMP = 21    // origin pin gpio 21
};
} // namespace rele

/**
 * @brief Definition regarding the IO pins identification
 * for devices control during the program execution.
 *
 * The attribute number are about the GPIOx
 */
enum class MASSAGEMOTOR {
  PWM_1 = 12,       // origin pin gpio 12
  PWM_2 = 13,       // origin pin gpio 13
  DIRECTION_1 = 26, // origin pin gpio 26
  DIRECTION_2 = 24  // origin pin gpio 24
};

enum class TANKSELECTOR {
  TANK_THERM = 5, // origin pin gpio 5
  TANK_CRYO = 6   // origin pin gpio 6

};

enum class SENSOR_SPI { CH0 = 0, CH1 = 1 };

} // namespace medicalhorse::hardware::iodefinition

#endif // MEDICALHORSE_IODEFINITION_H_
