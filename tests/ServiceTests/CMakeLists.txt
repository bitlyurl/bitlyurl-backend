cmake_minimum_required(VERSION 3.16)

find_package(Drogon REQUIRED)

function(add_service_tests bin_name path)
    add_executable(${bin_name} ${path})

    target_link_libraries(${bin_name} PRIVATE Drogon::Drogon PUBLIC core_url_service)

    ParseAndAddDrogonTests(${bin_name})
    
endfunction()

file(GLOB test_files LIST_DIRECTORIES FALSE "*.cpp")
foreach(file ${test_files})
    get_filename_component(name ${file} NAME_WE)
    add_service_tests(${name} ${file})
endforeach()