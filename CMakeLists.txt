cmake_minimum_required(VERSION 3.0.0)
project(solved_coderbyte_coding_challenges VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

include(CTest)
enable_testing()

add_executable(solved_coderbyte_coding_challenges 1_easy_difficulty_level/03_longest_word.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
