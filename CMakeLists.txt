cmake_minimum_required(VERSION 3.3)
project(engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#cpr
set(BUILD_CPR_TESTS NO)
set(USE_SYSTEM_CURL YES)
add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})

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
        include/slack/base/impl.h
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
        include/slack/fwd.h attachment.cpp include/slack/attachment.h incoming_webhook.cpp include/slack/incoming_webhook.h)

add_library(engine STATIC ${JSON_SOURCES} ${ENGINE_FILES})

set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
set(ENGINE_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

#tests
#TODO make this an option.
if (ENGINE_MAKE_TESTS)
    add_subdirectory(tests)
endif ()