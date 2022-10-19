cmake_minimum_required(VERSION 3.20)

find_package(Drogon REQUIRED)

function(add_repo_tests bin_name path)
    add_executable(${bin_name} ${path})

    target_link_libraries(${bin_name} PRIVATE Drogon::Drogon PUBLIC url_repository)

    ParseAndAddDrogonTests(${bin_name})
    
endfunction()

file(GLOB test_files LIST_DIRECTORIES FALSE "*.cpp")
foreach(file ${test_files})
    get_filename_component(name ${file} NAME_WE)
    add_repo_tests(${name} ${file})
endforeach()
