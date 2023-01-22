# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)
# Name of the project
# Create a few variables for the folder names, so they are easier to rename in
# the future
set(HARDWARE_DIR    ${CMAKE_CURRENT_LIST_DIR}/../repo/Hardware)
set(BOARD_DIR       ${CMAKE_CURRENT_LIST_DIR}/../repo/Board)
set(DEVCONTROL_DIR  ${CMAKE_CURRENT_LIST_DIR}/../repo/DeviceControl)
set(UTIL_DIR_COMMON ${CMAKE_CURRENT_LIST_DIR}/../../eletro-util/repo/Common)
set(UTIL_DIR_ERROR  ${CMAKE_CURRENT_LIST_DIR}/../../eletro-util/repo/Error)

# Variable definition to plot the PWM values in the screen
# add_definitions(-DPLOT_SIGNAL_DISPLAY)

# Add all the source files needed to build the executable
add_library(
    MedicalHorseBoard

    ${DEVCONTROL_DIR}/DeviceControl.cpp
    ${HARDWARE_DIR}/Device/Timer/Timer.cpp
    ${HARDWARE_DIR}/Device/Reles/Rele.cpp
    ${HARDWARE_DIR}/Device/Motor/Motor.cpp
    ${HARDWARE_DIR}/Device/HBridge/I2C/HBridge.cpp
    ${HARDWARE_DIR}/Device/HBridge/IO/HBridge.cpp
    ${HARDWARE_DIR}/Device/Sensor/DS1803.cpp
    ${HARDWARE_DIR}/Device/Sensor/MAX6675.cpp
    ${HARDWARE_DIR}/Interface/PWM/Pwm.cpp
    ${HARDWARE_DIR}/Interface/SerialBus/1Wire/OneWire.cpp
    ${HARDWARE_DIR}/Interface/SerialBus/I2C/I2C.cpp
    ${HARDWARE_DIR}/Interface/SerialBus/SPI/Spi.cpp
    ${BOARD_DIR}/Board.cpp
)

target_include_directories(MedicalHorseBoard PUBLIC ${BOARD_DIR})
target_include_directories(MedicalHorseBoard PUBLIC ${HARDWARE_DIR})
target_include_directories(MedicalHorseBoard PUBLIC ${DEVCONTROL_DIR})
target_include_directories(MedicalHorseBoard PUBLIC ${UTIL_DIR_COMMON})
target_include_directories(MedicalHorseBoard PUBLIC ${UTIL_DIR_ERROR})

target_link_libraries(MedicalHorseBoard Threads::Threads)
