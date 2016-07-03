cmake_minimum_required(VERSION 2.8)
project(engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

##### Options
macro(engine_option OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
    option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
    if (DEFINED ENV{${OPTION_NAME}})
        # Allow setting the option through an environment variable
        set(${OPTION_NAME} $ENV{${OPTION_NAME}})
    endif ()
    if (${OPTION_NAME})
        add_definitions(-D${OPTION_NAME})
    endif ()
    message(STATUS "  ${OPTION_NAME}: ${${OPTION_NAME}}")
endmacro()

message(STATUS "Engine CMake Options")
message(STATUS "=======================================================")
engine_option(BUILD_ENGINE_TESTS "Build the test suite" OFF)
engine_option(BUILD_ENGINE_EXAMPLES "Build the examples" OFF)
message(STATUS "=======================================================")


##### Engine

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

include_directories(SYSTEM
        ${PROJECT_SOURCE_DIR}
        )

set(ENGINE_FILES slack/slack.h slack/slack.cpp slack/slack.h)

add_library(engine STATIC ${ENGINE_FILES})

target_link_libraries(engine ${CONAN_LIBS})


##### Testing
if (BUILD_ENGINE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()



##### Examples
if (BUILD_ENGINE_EXAMPLES)
    add_subdirectory(examples)
endif ()
