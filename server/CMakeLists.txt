# server/CMakeLists.txt

# Specifically for the supervisor lib
set(LIB_SOURCES
    supervisor.cpp
)
add_library(orphan_sock_server_impl ${LIB_SOURCES})

target_include_directories(
    orphan_sock_server_impl
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Daemon sources
set(SOURCES
    main.cpp
    server.cpp
)
# Create the orphan_sock daemon executable
# Let's call it orphan_sockd (since its a daemon)
add_executable(orphan_sockd ${SOURCES})

target_link_libraries(orphan_sockd
    PRIVATE
        orphan_sock_server_impl
        orphan_sock_proto
)
