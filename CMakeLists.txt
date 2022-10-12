cmake_minimum_required(VERSION 3.20)

project("bitlyurl-backend" CXX)


set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("src")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)