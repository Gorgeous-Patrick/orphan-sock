# Project name + language
project(orphansocks_server LANGUAGES C CXX)

# Add your source files
set(SOURCES supervisor.cpp main.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
