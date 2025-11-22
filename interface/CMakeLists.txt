project(orphan_sock_proto CXX)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++17 (or whatever you want)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(gRPC CONFIG REQUIRED)

# Where your .proto files live
set(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROTO_FILES
    "${PROTO_DIR}/orphan_sock.proto"
)

# Output directory for generated sources
set(GENERATED_PROTO_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${GENERATED_PROTO_DIR}")

# Tell CMake where to find the generated headers
include_directories(${GENERATED_PROTO_DIR})

# Custom command to run protoc + grpc_cpp_plugin
set(PROTO_SRCS "")
set(PROTO_HDRS "")
set(GRPC_SRCS "")
set(GRPC_HDRS "")

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME "${PROTO_FILE}" NAME_WE)

    list(APPEND PROTO_SRCS "${GENERATED_PROTO_DIR}/${PROTO_NAME}.pb.cc")
    list(APPEND PROTO_HDRS "${GENERATED_PROTO_DIR}/${PROTO_NAME}.pb.h")
    list(APPEND GRPC_SRCS  "${GENERATED_PROTO_DIR}/${PROTO_NAME}.grpc.pb.cc")
    list(APPEND GRPC_HDRS  "${GENERATED_PROTO_DIR}/${PROTO_NAME}.grpc.pb.h")

    add_custom_command(
        OUTPUT
            "${GENERATED_PROTO_DIR}/${PROTO_NAME}.pb.cc"
            "${GENERATED_PROTO_DIR}/${PROTO_NAME}.pb.h"
            "${GENERATED_PROTO_DIR}/${PROTO_NAME}.grpc.pb.cc"
            "${GENERATED_PROTO_DIR}/${PROTO_NAME}.grpc.pb.h"
        COMMAND protobuf::protoc
            ARGS
                --proto_path=${PROTO_DIR}
                --cpp_out=${GENERATED_PROTO_DIR}
                --grpc_out=${GENERATED_PROTO_DIR}
                --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
                ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating C++ and gRPC sources from ${PROTO_FILE}"
        VERBATIM
    )
endforeach()

# Library that contains all generated code
add_library(orphan_sock_proto
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    ${GRPC_SRCS}
    ${GRPC_HDRS}
)

target_link_libraries(orphan_sock_proto
    PUBLIC
        gRPC::grpc++
        protobuf::libprotobuf
)

target_include_directories(orphan_sock_proto
    PUBLIC
        ${GENERATED_PROTO_DIR}
)
