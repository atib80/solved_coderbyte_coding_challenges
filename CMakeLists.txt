cmake_minimum_required(VERSION 3.0.0)
set(This solved_coderbyte_coding_challenges)
project(${This} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/nologo /W4 /EHsc /Ot /Ox /Ob2 /Oy /Oi)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -O3 -Ofast)
endif ()

include(CTest)
enable_testing()

set(headers        
        include/stl_helper_functions.hpp        
        )

set(sources
        1_easy_difficulty_level/46_two_sum.cpp
        )

add_executable(${This} ${headers} ${sources})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
