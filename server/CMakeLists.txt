# Project name + language
project(orphansocks_server LANGUAGES C CXX)

# Add your source files
set(LIB_SOURCES supervisor.cpp)
set(SOURCES main.cpp)


add_library(orphan_sock_server_impl ${LIB_SOURCES})

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../interface/generated)
target_link_libraries(${PROJECT_NAME}
    PRIVATE orphan_sock_server_impl
)
