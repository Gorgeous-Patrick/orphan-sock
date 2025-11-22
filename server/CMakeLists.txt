# Project name + language
project(orphansocks_server LANGUAGES C CXX)

# Add your source files
set(SOURCES supervisor.cpp main.cpp)

# Set the output folder for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Set the output folder for static and shared libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Set the output folder for archive targets (import libraries for DLLs on Windows)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
