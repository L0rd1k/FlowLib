cmake_minimum_required(VERSION 3.19...3.20)

include_directories(.)

project(CCFlow
    VERSION 1.0.0
    LANGUAGES CXX)

set(SOURCES main.cpp)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if(${CMAKE_CXX_COMPILER_VERSION} LESS_EQUAL "10.0")
        set(CMAKE_CXX_STANDARD 17)
    else()
        set(CMAKE_CXX_STANDARD 20)
        set(CMAKE_CXX_FLAGS "-pthread -fcoroutines")
        list(APPEND SOURCES
            src/coroutines/core/coro_core.cpp
            src/coroutines/launcher/launcher.cpp
            src/coroutines/thread/thread_launcher.cpp
        )
        add_definitions(-DUSE_COROUTINES=ON)
    endif()
else()
endif()

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# ------------ GTEST ------------
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)
add_executable(TestCallback tests/callback_test.cpp)
target_link_libraries(TestCallback GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TestCallback)