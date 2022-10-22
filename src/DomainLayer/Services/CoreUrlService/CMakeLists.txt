cmake_minimum_required(VERSION 3.16)

add_library(core_url_service STATIC "CoreUrlService.cpp")
target_include_directories(core_url_service PUBLIC "../..")

target_link_libraries(core_url_service PUBLIC url_repository)