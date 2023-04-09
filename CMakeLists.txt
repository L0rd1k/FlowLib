cmake_minimum_required(VERSION 3.19...3.20)

include_directories(.)

project(CCFlow
    VERSION 1.0.0
    LANGUAGES CXX)

set(SOURCES main.cpp)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if(${CMAKE_CXX_COMPILER_VERSION} LESS_EQUAL "10.0")
        set(CMAKE_CXX_STANDARD 14)
    else()
        set(CMAKE_CXX_STANDARD 20)
        list(APPEND SOURCES
            src/coroutines/core/coro_core.cpp
            src/coroutines/launcher/launcher.cpp
            src/coroutines/thread/thread_launcher.cpp
        )
        add_definitions(-DUSE_COROUTINES=ON)
    endif()
else()
endif()

list(APPEND SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})