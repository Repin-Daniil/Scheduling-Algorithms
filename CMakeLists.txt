cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_library(SchedulerLib STATIC
        src/Scheduler/Scheduler.h
        src/Scheduler/Scheduler.cpp

        src/Scheduler/Lab_1/SchedulerFCFS.h
        src/Scheduler/Lab_2/SchedulerRR.h
        src/Scheduler/Lab_2/SchedulerSJF.h
        src/Scheduler/Lab_3/SchedulerRR_SJF.h
        src/Scheduler/Lab_3/SchedulerPSJF.h

        src/Scheduler/Lab_1/SchedulerFCFS.cpp
        src/Scheduler/Lab_2/SchedulerRR.cpp
        src/Scheduler/Lab_2/SchedulerSJF.cpp
        src/Scheduler/Lab_3/SchedulerRR_SJF.cpp
        src/Scheduler/Lab_3/SchedulerPSJF.cpp)

add_executable(Scheduler src/main.cpp
        src/Application/Application.h
        src/Window/Window.h
        src/constants_storage.h


        src/Application/Application.cpp
        src/Window/Window.cpp
        )

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


#TESTS
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)
add_executable(scheduler_tests tests/scheduler_tests.cpp)

target_link_libraries(scheduler_tests PRIVATE SchedulerLib Catch2::Catch2WithMain)

#Or with catch.hpp
#add_executable(SchedulerTest tests/scheduler_tests.cpp  catch.hpp)
#target_link_libraries(SchedulerTest SchedulerLib)