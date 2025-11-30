# tests/CMakeLists.txt

set(TEST_TARGETS
    test_basic_client
    # ...
)

foreach(test_name IN LISTS TEST_TARGETS)
    add_executable(${test_name}
        ${test_name}.cpp
    )

    target_link_libraries(${test_name}
        PRIVATE
            liborphan_sock   # <-- ONLY the client lib
            # pthread or whatever
    )
endforeach()