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
engine_option(BUILD_ENGINE_COVERAGE "Generate test coverage information"    OFF)
engine_option(BUILD_ENGINE_EXAMPLES "Build the examples" OFF)
message(STATUS "=======================================================")

if (BUILD_ENGINE_COVERAGE)
    set(BUILD_ENGINE_TESTS true) # need the tests if coverage is requested!

    if(NOT (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
            AND (NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"))
        message(FATAL_ERROR "Coveralls: Compiler ${CMAKE_C_COMPILER_ID} is not GNU gcc! Aborting... You can set this on the command line using CC=/usr/bin/gcc CXX=/usr/bin/g++ cmake <options> ..")
    endif()

    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(FATAL_ERROR "Coveralls: Code coverage results with an optimised (non-Debug) build may be misleading! Add -DCMAKE_BUILD_TYPE=Debug")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()

##### JSONCPP
#
#set(JSONCPP_INCLUDE_DIR jsoncpp)
#set(JSON_SOURCES jsoncpp/jsoncpp.cpp)
#include_directories(SYSTEM ${JSONCPP_INCLUDE_DIR})

##### Engine

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

include_directories(SYSTEM
        ${PROJECT_SOURCE_DIR}
        )
include_directories(
        ${PROJECT_SOURCE_DIR}/slack
        ${PROJECT_SOURCE_DIR}/slack/private
        )

set(ENGINE_FILES
        slack/slack.h
        slack/slack.cpp
        slack/slack.h
        slack/set_option.h
        slack/chat.h
        slack/web/api.test.cpp
        slack/web/api.test.h
        slack/web/channels.archive.cpp
        slack/web/channels.archive.h
        slack/web/channels.list.cpp
        slack/web/channels.list.h
        slack/web/chat.delete.cpp
        slack/web/chat.delete.h
        slack/web/chat.update.cpp
        slack/web/chat.update.h
        slack/web/rtm.start.cpp
        slack/web/rtm.start.h
        slack/web/auth.test.cpp
        slack/web/auth.test.h
        slack/web/channels.create.cpp
        slack/web/channels.create.h
        slack/web/channels.rename.cpp
        slack/web/channels.rename.h
        slack/web/chat.postMessage.cpp
        slack/web/chat.postMessage.h
        slack/web/oauth.access.cpp
        slack/web/oauth.access.h
        slack/types.h
        slack/fwd.h
        slack/optional.hpp
        slack/attachment.h
        slack/private/private.h
        slack/private/private.cpp
        slack/base/response.h
        slack/base/event.h
        slack/attachment.cpp
        slack/event/channel_archive.cpp
        slack/event/message.cpp
        slack/event/message_channel_archive.cpp
        slack/event/pong.cpp
        slack/event/channel_archive.h
        slack/event/message.h
        slack/event/message_channel_archive.h
        slack/event/pong.h
        slack/event/hello.cpp
        slack/event/message_bot_message.cpp
        slack/event/message_me_message.cpp
        slack/event/user_typing.cpp
        slack/event/hello.h
        slack/event/message_bot_message.h
        slack/event/message_me_message.h
        slack/event/user_typing.h
        slack/types.cpp
        slack/uricodec.cpp
        slack/uricodec.h
        slack/base/slack_delegate.h
        slack/channel.cpp
        slack/http.h
        slack/api.h
        slack/auth.h
        slack/oauth.h
        slack/rtm.h
        slack/channels.h
        slack/private/events_private.h
        slack/event/unknown.cpp
        slack/event/unknown.h
        slack/base/event.cpp
        slack/event/events.h
        slack/http_event_client.cpp
        slack/http_event_client.h
        slack/rtm_event_client.cpp
        slack/rtm_event_client.h
        slack/private/events_private.cpp slack/message_router.cpp slack/message_router.h)

add_library(engine STATIC ${ENGINE_FILES})

target_link_libraries(engine ${CONAN_LIBS})

##### Testing
if (BUILD_ENGINE_TESTS)
    add_subdirectory(tests)
endif ()



##### Examples
if (BUILD_ENGINE_EXAMPLES)
    add_subdirectory(examples)
endif ()
