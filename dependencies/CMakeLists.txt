cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)
FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1)
FetchContent_MakeAvailable(Catch2)