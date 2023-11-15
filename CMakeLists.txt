cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Scheduler src/main.cpp
                         src/Application/Application.h
                         src/Scheduler/Scheduler.h
                         src/Window/Window.h
                         src/constants_storage.h
                         src/Scheduler/Lab_1/SchedulerFCFS.h
                         src/Scheduler/Lab_2/SchedulerRR.h
                         src/Application/Application.cpp
                         src/Scheduler/Scheduler.cpp
                         src/Window/Window.cpp
                         src/Scheduler/Lab_1/SchedulerFCFS.cpp
                         src/Scheduler/Lab_2/SchedulerRR.cpp)

target_link_libraries(Scheduler PRIVATE sfml-graphics)
target_compile_features(Scheduler PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET Scheduler
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Scheduler>
            VERBATIM)
endif ()

install(TARGETS Scheduler)
