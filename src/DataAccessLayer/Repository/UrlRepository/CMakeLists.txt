cmake_minimum_required(VERSION 3.16)


add_library(url_repository STATIC "UrlRepository.cpp")
target_include_directories(url_repository PUBLIC "../..")
