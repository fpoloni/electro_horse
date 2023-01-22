# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Create a few variables for the folder names, so they are easier to rename in
# the future
set(SRC_DIR     repo/Application)
set(COMMAND_DIR repo/Command)
set(DISPLAY_DIR ../eletro-display/repo/src)
set(UTIL_DIR ../)


# Add all the source files needed to build the executable
add_executable(
    Application

    ${SRC_DIR}/Application.cpp
    ${SRC_DIR}/ProgramProcess.cpp
    ${COMMAND_DIR}/CommandHandler.cpp
)

target_include_directories(Application PUBLIC ${COMMAND_DIR})
target_include_directories(Application PUBLIC ${DISPLAY_DIR})
target_include_directories(Application PUBLIC ${UTIL_DIR})


target_link_libraries(Application PUBLIC MedicalHorseUtil)
target_link_libraries(Application PUBLIC MedicalHorseBoard)
target_link_libraries(Application PUBLIC MedicalHorseDisplay)