cmake_minimum_required(VERSION 3.17)
project(bit_array_test C)

enable_testing()

set(CMAKE_C_STANDARD 99)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(isDebug TRUE)
else()
    set(isDebug FALSE)
endif()

if (isDebug)
    message("Debug build detected")
    add_compile_definitions(CONFIGURATION_DEBUG TYRAN_CONFIGURATION_DEBUG)
    set(CONFIGURATION_DEBUG 1)
endif()


add_executable(bit_array_test
    main.c
    test.c
)

add_test(NAME bit_array_test
         COMMAND bit_array_test)

if (WIN32)
target_link_libraries(bit_array_test PRIVATE bit-array)
else()
target_link_libraries(bit_array_test PRIVATE bit-array m)
endif()
