cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(Scheduling-Algorithms LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif ()

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_library(SchedulerLib STATIC
        src/Scheduler/Scheduler.h
        src/Scheduler/SchedulerFactory.h
        src/constants_storage.h

        src/Scheduler/Lab_1/SchedulerFCFS.h
        src/Scheduler/Lab_2/SchedulerRR.h
        src/Scheduler/Lab_2/SchedulerSJF.h
        src/Scheduler/Lab_3/SchedulerRR_SJF.h
        src/Scheduler/Lab_3/SchedulerPSJF.h

        src/Scheduler/Scheduler.cpp
        src/Scheduler/Lab_1/SchedulerFCFS.cpp
        src/Scheduler/Lab_2/SchedulerRR.cpp
        src/Scheduler/Lab_2/SchedulerSJF.cpp
        src/Scheduler/Lab_3/SchedulerRR_SJF.cpp
        src/Scheduler/Lab_3/SchedulerPSJF.cpp)

add_executable(Scheduler src/main.cpp
        src/Application/Application.h
        src/Window/Window.h

        src/Application/Application.cpp
        src/Window/Window.cpp)

target_link_libraries(Scheduler PRIVATE SchedulerLib sfml-graphics)
target_compile_features(Scheduler PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET Scheduler
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Scheduler>
            VERBATIM)
endif ()

install(TARGETS Scheduler)

# TESTS
# Catch2
add_executable(FCFS_TEST tests/Scheduler/Lab_1/FCFS_tests.cpp catch.hpp)
target_link_libraries(FCFS_TEST SchedulerLib)

add_executable(RR_TEST tests/Scheduler/Lab_2/RR_tests.cpp catch.hpp)
target_link_libraries(RR_TEST SchedulerLib)

add_executable(SJF_TEST tests/Scheduler/Lab_2/SJF_tests.cpp catch.hpp)
target_link_libraries(SJF_TEST SchedulerLib)

add_executable(RR_SJF_TEST tests/Scheduler/Lab_3/RR_SJF_tests.cpp catch.hpp)
target_link_libraries(RR_SJF_TEST SchedulerLib)

add_executable(PSJF_TEST tests/Scheduler/Lab_3/PSJF_tests.cpp catch.hpp)
target_link_libraries(PSJF_TEST SchedulerLib)

# CTest
enable_testing()
add_test(NAME FCFS COMMAND FCFS_TEST)
add_test(NAME RR COMMAND RR_TEST)
add_test(NAME SJF COMMAND SJF_TEST)
add_test(NAME RR_SJF COMMAND RR_SJF_TEST)
add_test(NAME PSJF COMMAND PSJF_TEST)

#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG v3.4.0 # or a later release
#)
#
#FetchContent_MakeAvailable(Catch2)
#add_executable(scheduler_tests tests/scheduler_tests.cpp)
#
#target_link_libraries(scheduler_tests PRIVATE SchedulerLib Catch2::Catch2WithMain)