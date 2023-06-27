cmake_minimum_required(VERSION 3.17)
project(bit_array C)

add_subdirectory("deps/piot/clog/src/lib")
add_subdirectory("deps/piot/tiny-libc/src/lib")
add_subdirectory("deps/piot/imprint/src/lib")
add_subdirectory("lib")
add_subdirectory("test")
