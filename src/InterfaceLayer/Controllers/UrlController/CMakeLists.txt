cmake_minimum_required(VERSION 3.20)


add_library(url_controller STATIC "UrlController.cpp")
target_include_directories(url_controller PUBLIC "../..")

target_link_libraries(url_controller PUBLIC core_url_service)
# here mustbe linkage with services from Domain Layer