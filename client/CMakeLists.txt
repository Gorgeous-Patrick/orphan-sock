# client/CMakeLists.txt

set(LOSOCK_SRC "osock_client.cpp")
set(LOSOCK_HDR "osock_client.cpp")

add_library(liborphan_sock
    ${LOSOCK_SRC}
    ${LOSOCK_HDR}
)

target_link_libraries(liborphan_sock
    PRIVATE
        orphan_sock_proto
)

target_include_directories(liborphan_sock
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)