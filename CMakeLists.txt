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

##### JSONCPP

set(JSONCPP_INCLUDE_DIR jsoncpp)
set(JSON_SOURCES jsoncpp/jsoncpp.cpp)
include_directories(SYSTEM ${JSONCPP_INCLUDE_DIR})

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
        ${JSON_SOURCES}
        slack/slack.h
        slack/slack.cpp
        slack/slack.h
        slack/set_option.h
        slack/chat.cpp
        slack/chat.h
        slack/chat.postMessage.cpp
        slack/chat.postMessage.h
        slack/types.h
        slack/fwd.h
        slack/optional.hpp
        slack/attachment.h
        slack/private/private.h
        slack/private/private.cpp
        slack/base/response.h
        slack/base/event.h
        slack/event.h
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
        slack/types.cpp slack/uricodec.cpp slack/uricodec.h slack/base/slack_delegate.h)

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
