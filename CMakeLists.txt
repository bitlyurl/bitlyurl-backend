cmake_minimum_required(VERSION 3.16)

enable_testing()

project("bitlyurl-backend" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-unused-parameter)

add_subdirectory("src")
add_subdirectory("tests" EXCLUDE_FROM_ALL)
