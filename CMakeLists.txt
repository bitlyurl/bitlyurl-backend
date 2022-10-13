cmake_minimum_required(VERSION 3.20)

project("bitlyurl-backend" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory("src")

