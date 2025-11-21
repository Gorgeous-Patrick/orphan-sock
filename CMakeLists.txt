cmake_minimum_required(VERSION 3.16)

# Project name + language
project(OrphanSocks LANGUAGES C CXX)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files
set(SOURCES supervisor.cpp main.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
