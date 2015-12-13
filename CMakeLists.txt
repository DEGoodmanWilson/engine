cmake_minimum_required(VERSION 3.3)
project(engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#cpr
set(BUILD_CPR_TESTS NO)
set(USE_SYSTEM_CURL YES)
add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})

#websockets
#add_subdirectory(Simple-WebSocket-Server)
include_directories(Simple-WebSocket-Server)


# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_COMPONENTS system regex filesystem thread)
find_package(Boost 1.53 REQUIRED ${Boost_COMPONENTS})
include_directories(${Boost_INCLUDE_DIR})


# OpenSSL
#set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/1.0.2d_1/)
#find_package(OpenSSL 1.0.2 REQUIRED)
# OpenSSL, because brew.
set(OPENSSL_INCLUDE_DIR /usr/local/opt/openssl/include)
set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)
set(OPENSSL_LIBRARIES ssl crypto)
include_directories(${OPENSSL_INCLUDE_DIR})
link_directories(${OPENSSL_LIB_DIR})


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
        )

add_library(engine STATIC ${JSON_SOURCES} ${ENGINE_FILES})

target_link_libraries(engine cpr ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
set(ENGINE_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

#tests
#TODO make this an option.
if (ENGINE_MAKE_TESTS)
    add_subdirectory(tests)
endif ()