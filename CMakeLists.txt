cmake_minimum_required(VERSION 3.3)
project(engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

##### Options

macro(engine_option OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
    option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
    if(DEFINED ENV{${OPTION_NAME}})
        # Allow setting the option through an environment variable
        set(${OPTION_NAME} $ENV{${OPTION_NAME}})
    endif()
    if(${OPTION_NAME})
        add_definitions(-D${OPTION_NAME})
    endif()
    message(STATUS "  ${OPTION_NAME}: ${${OPTION_NAME}}")
endmacro()

message(STATUS "Engine CMake Options")
message(STATUS "=======================================================")
engine_option(BUILD_ENGINE_TESTS    "Build the test suite"            ON)
message(STATUS "=======================================================")

# Conan
include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

#websockets
#add_subdirectory(Simple-WebSocket-Server)
include_directories(Simple-WebSocket-Server)




# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_COMPONENTS system regex filesystem thread)
find_package(Boost 1.53 REQUIRED ${Boost_COMPONENTS})
include_directories(${Boost_INCLUDE_DIR})


#jsoncpp
set(JSONCPP_INCLUDE_DIR jsoncpp)
set(JSON_SOURCES jsoncpp/jsoncpp.cpp)


include_directories(SYSTEM
        ${JSONCPP_INCLUDE_DIR}
        include
        .
        )


set(ENGINE_FILES
        uricodec.h
        uricodec.cpp
        include/slack/slack.h
        types.cpp
        include/slack/types.h
        include/slack/config.h
        config.h
        config.cpp
        base/response.cpp
        include/slack/base/response.h
        private.h
        include/slack/http.h
        http.cpp
        include/slack/set_option.h
        include/slack/api.test.h
        api.test.cpp
        include/slack/auth.test.h
        auth.test.cpp
        include/slack/channels.list.h
        channels.list.cpp
        include/slack/channels.create.h
        channels.create.cpp
        include/slack/channels.archive.h
        channels.archive.cpp
        include/slack/chat.delete.h
        chat.delete.cpp
        include/slack/chat.post_message.h
        chat.post_message.cpp
        include/slack/chat.update.h
        chat.update.cpp
        include/slack/rtm.start.h
        rtm.start.cpp
        include/slack/oauth.access.h
        oauth.access.cpp
        channels.rename.cpp
        include/slack/channels.rename.h
        private.cpp
        include/slack/fwd.h
        attachment.cpp
        include/slack/attachment.h
        incoming_webhook.cpp
        include/slack/incoming_webhook.h
        real_time_client.cpp
        include/slack/real_time_client.h
        event.cpp
        include/slack/base/event.h
        include/slack/event/hello.h
        event/hello.cpp
        event/user_typing.cpp
        include/slack/event/user_typing.h
        include/slack/event.h
        include/slack/websocket.h
        websocket.cpp
        include/slack/event/pong.h
        event/pong.cpp
        include/slack/event/message.h
        event/message.cpp
        include/slack/event/channel_archive.h
        event/channel_archive.cpp
        include/slack/event/message_channel_archive.h
        event/message_channel_archive.cpp
        include/slack/channel.h
        include/slack/event/message_bot_message.h
        event/message_bot_message.cpp
        include/slack/event/message_me_message.h
        event/message_me_message.cpp
        channel.cpp
        )

add_library(engine STATIC ${JSON_SOURCES} ${ENGINE_FILES})

target_link_libraries(engine ${Boost_LIBRARIES} ${CONAN_LIBS})

set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
set(ENGINE_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

#tests
message(ERROR "${BUILD_ENGINE_TESTS}")
#TODO make this an option.
if (BUILD_ENGINE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()