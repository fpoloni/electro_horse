# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Add all the source files needed to build the executable
add_library(
    MedicalHorseDisplay
    ${CMAKE_CURRENT_SOURCE_DIR}/repo/c/src/Display/Display.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/repo/c/src/Comm/TcpIpComm.cpp
)

target_include_directories(MedicalHorseDisplay PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/repo/c/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/repo/c/src/Comm/
    ${CMAKE_CURRENT_SOURCE_DIR}../util/repo/HandlePackage/
    ${CMAKE_CURRENT_SOURCE_DIR}../util/repo/Common/
)

target_link_libraries(MedicalHorseDisplay PUBLIC MedicalHorseUtil)
