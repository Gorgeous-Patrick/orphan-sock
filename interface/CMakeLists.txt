# interface/CMakeLists.txt

find_package(Protobuf REQUIRED)

# Where .proto files live
set(PROTO_DIR    "${CMAKE_CURRENT_SOURCE_DIR}")
set(OSOCK        "orphan_sock"                ) # same as project name, but setting anyway
set(PROTO_FILES  "${PROTO_DIR}/${OSOCK}.proto")

# Output directory for generated sources
set(GEN_PROTO_DIR   "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${GEN_PROTO_DIR}")

set(PROTO_SRCS "${GEN_PROTO_DIR}/${OSOCK}.pb.cc")
set(PROTO_HDRS "${GEN_PROTO_DIR}/${OSOCK}.pb.h")
# Run protoc
add_custom_command(
    OUTPUT
        ${PROTO_SRCS}
        ${PROTO_HDRS}
    COMMAND protobuf::protoc
        ARGS
            --proto_path=${PROTO_DIR}
            --cpp_out=${GEN_PROTO_DIR}
            ${PROTO_FILES}
        DEPENDS ${PROTO_FILES}
        COMMENT "Generating C++ protobuf sources from ${PROTO_FILES}"
        VERBATIM
)

# Library that contains all generated code
add_library(orphan_sock_proto
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_link_libraries(orphan_sock_proto
    PUBLIC
        protobuf::libprotobuf
)

target_include_directories(orphan_sock_proto
    PUBLIC
        ${GEN_PROTO_DIR}
)

# Keeping old stuff here for reference
    # Generate compile_commands.json ( set at top level )
    # ALso no need to set CPP standar options here
    # find_package(gRPC CONFIG REQUIRED) # no gRPC
    #
    #
    # Tell CMake where to find the generated headers
    #    needed??
    # include_directories(${GEN_PROTO_DIR})
    #
    #
    # # No need for this initializer + loop as far as I can tell. Ported to above pending
    #                                                        a need for more .pbs
    # # Custom command to run protoc + grpc_cpp_plugin
    # set(PROTO_SRCS "")
    # set(PROTO_HDRS "")
    # # set(GRPC_SRCS "")
    # # set(GRPC_HDRS "")
    #
    # foreach(PROTO_FILE ${PROTO_FILES})
    #     get_filename_component(PROTO_NAME "${PROTO_FILE}" NAME_WE)
    #
    #     list(APPEND PROTO_SRCS "${GEN_PROTO_DIR}/${PROTO_NAME}.pb.cc")
    #     list(APPEND PROTO_HDRS "${GEN_PROTO_DIR}/${PROTO_NAME}.pb.h")
    #     # list(APPEND GRPC_SRCS  "${GEN_PROTO_DIR}/${PROTO_NAME}.grpc.pb.cc")
    #     # list(APPEND GRPC_HDRS  "${GEN_PROTO_DIR}/${PROTO_NAME}.grpc.pb.h")
    #
    #     add_custom_command(
    #         OUTPUT
    #             "${GEN_PROTO_DIR}/${PROTO_NAME}.pb.cc"
    #             "${GEN_PROTO_DIR}/${PROTO_NAME}.pb.h"
    #             # "${GEN_PROTO_DIR}/${PROTO_NAME}.grpc.pb.cc"
    #             # "${GEN_PROTO_DIR}/${PROTO_NAME}.grpc.pb.h"
    #         COMMAND protobuf::protoc
    #             ARGS
    #                 --proto_path=${PROTO_DIR}
    #                 --cpp_out=${GEN_PROTO_DIR}
    #                 # --grpc_out=${GEN_PROTO_DIR}
    #                 # --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
    #                 ${PROTO_FILE}
    #         DEPENDS ${PROTO_FILE}
    #         COMMENT "Generating C++ and gRPC sources from ${PROTO_FILE}" # no more gRPC
    #         VERBATIM
    #     )
    # endforeach()
    # Library that contains all generated code
    # add_library(orphan_sock_proto
    #     ${PROTO_SRCS}
    #     ${PROTO_HDRS}
    #     # ${GRPC_SRCS}
    #     # ${GRPC_HDRS}
    # )

    # target_link_libraries(orphan_sock_proto
    #     PUBLIC
    #         #gRPC::grpc++ # should be no gRPC
    #         protobuf::libprotobuf
    # )

    # target_include_directories(orphan_sock_proto
    #     PUBLIC
    #         ${GEN_PROTO_DIR}
    # )