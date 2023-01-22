# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Name of the project
project(MedicalHorse)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)          #non-optimized code with debug symbols
#set(CMAKE_BUILD_TYPE RelWithDebInfo) #optimized code with debug symbols

if ($ENV{MD_CROSS_COMPILING})
    message(STATUS "Cross compiling to ARM/RaspberryPI")

    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)

    set(TOOLCHAIN_PREFIX $ENV{SYSROOTS}/usr/bin/arm-linux-gnueabihf)
    set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

    set(CMAKE_CROSSCOMPILING 1)
else()
    message(STATUS "Compiling to X86")
endif()

# Static libraries
add_subdirectory(eletro-display)
add_subdirectory(eletro-util)
add_subdirectory(eletro-board)

# Application
add_subdirectory(eletro-app)
