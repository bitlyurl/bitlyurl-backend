cmake_minimum_required(VERSION 3.20)

add_executable(${PROJECT_NAME} main.cpp)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

add_subdirectory("InterfaceLayer/")
add_subdirectory("DomainLayer/")
add_subdirectory("DataAccessLayer/")

target_link_libraries(${PROJECT_NAME} PRIVATE url_controller)