# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

add_executable(BoardAppTest
    ${CMAKE_CURRENT_LIST_DIR}/Main.cpp
)

target_include_directories(BoardAppTest PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../Hardware/
    ${CMAKE_CURRENT_LIST_DIR}/../Hardware/Device/HBridge/
    ${CMAKE_CURRENT_LIST_DIR}/../Hardware/Device/Sensor/
    ${CMAKE_CURRENT_LIST_DIR}/../Hardware/Interface/SerialBus/SPI/
    ${CMAKE_CURRENT_LIST_DIR}/../Hardware/Interface/SerialBus/I2C/
    ${CMAKE_CURRENT_LIST_DIR}/../Hardware/Interface/SerialBus/1Wire/
)

target_link_libraries(BoardAppTest MedicalHorseBoard)
