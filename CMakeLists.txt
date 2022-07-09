cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(This solved_coderbyte_coding_challenges)
project(${This} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

if (MSVC)
    add_compile_options(/nologo /std:c++17 /W4 /EHsc /Od)
else ()
    add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -O0 -g)
endif ()

add_subdirectory(dependencies)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(CTest)

set(sources 1_easy_difficulty_level/10_alphabet_soup.cpp)

add_executable(${This} ${sources})
target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${This} PUBLIC Catch2)
target_link_libraries(${This} PUBLIC Catch2::Catch2WithMain)

add_test(
    NAME ${This}
    COMMAND ${This}
)

