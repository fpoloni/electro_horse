# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Create a few variables for the folder names, so they are easier to rename in
# the future
set(REPO_DIR
    repo/Error
    repo/Package
    repo/Queue
    repo/Common
    repo/HandlePackage
)


# Add all the source files needed to build the executable
add_library(
    MedicalHorseUtil
    repo/HandlePackage/HandlePackage.cpp
)

target_include_directories(MedicalHorseUtil PUBLIC ${REPO_DIR})
