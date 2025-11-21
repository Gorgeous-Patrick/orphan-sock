cmake_minimum_required(VERSION 3.16)

# Project name + language
project(MyProject LANGUAGES C CXX)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files
set(SOURCES supervisor.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories (if any)
# target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries (if any)
# target_link_libraries(${PROJECT_NAME} PRIVATE m)
