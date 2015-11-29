cmake_minimum_required(VERSION 3.3)
project(cpp-slack-client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#lib

#add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS)

# Boost
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_COMPONENTS system regex filesystem thread)
#find_package(Boost 1.53 REQUIRED ${Boost_COMPONENTS})

# OpenSSL
#set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/1.0.2d_1/)
#find_package(OpenSSL 1.0.2 REQUIRED)
# OpenSSL, because brew.
set(OPENSSL_INCLUDE_DIR /usr/local/Cellar/openssl/1.0.2d_1/include)
set(OPENSSL_LIB_DIR /usr/local/Cellar/openssl/1.0.2d_1/lib)
set(OPENSSL_LIBRARIES ssl crypto)
link_directories(${OPENSSL_LIB_DIR})


#cpr
set(USE_SYSTEM_CURL YES)
add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})


#jsoncpp
set(JSONCPP_INCLUDE_DIR jsoncpp)
set(JSON_SOURCES jsoncpp/jsoncpp.cpp)


#simple-web-socket
set(SIMPLEWEB_INCLUDE_DIR SimpleWeb)

#optional
set(OPTIONAL_INCLUDE_DIR optional)


include_directories(SYSTEM
        ${CPP_NETLIB_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        ${JSONCPP_INCLUDE_DIR}
        ${SIMPLEWEB_INCLUDE_DIR}
        #        ${NOD_INCLUDE_DIR}
        ${OPTIONAL_INCLUDE_DIR}
        include
        .
        )


set(SLACK_FILES
        include/slack/slack.h
        types.cpp
        include/slack/types.h
        config.cpp
        include/slack/config.h
        config.h
        base/response.cpp
        include/slack/base/response.h
        include/slack/base/impl.h
        include/slack/api.h
        api/impl/test.cpp
        include/slack/api/impl/test.h
        api/parameter/test.cpp
        include/slack/api/parameter/test.h
        api/response/test.cpp
        include/slack/api/response/test.h
        api/test.cpp
        include/slack/api/test.h
#        include/slack/auth.h
#        auth/impl/test.cpp
#        include/slack/auth/impl/test.h
#        auth/parameter/test.cpp
#        include/slack/auth/parameter/test.h
#        auth/response/test.cpp
#        include/slack/auth/response/test.h
#        auth/test.cpp
#        include/slack/auth/test.h
#        include/slack/channels.h
#        channels/impl/list.cpp
#        include/slack/channels/impl/list.h
#        include/slack/channels/list.h
#        include/slack/channels/parameter/list.h
#        channels/response/list.cpp
#        include/slack/channels/response/list.h
#        include/slack/chat.h
#        chat/delete.cpp
#        include/slack/chat/delete.h
#        chat/impl/delete.cpp
#        include/slack/chat/impl/delete.h
#        chat/impl/post_message.cpp
#        include/slack/chat/impl/post_message.h
#        chat/impl/update.cpp
#        include/slack/chat/impl/update.h
#        chat/parameter/delete.cpp
#        include/slack/chat/parameter/delete.h
#        chat/parameter/post_message.cpp
#        include/slack/chat/parameter/post_message.h
#        chat/parameter/update.cpp
#        include/slack/chat/parameter/update.h
#        chat/post_message.cpp
#        include/slack/chat/post_message.h
#        chat/response/delete.cpp
#        include/slack/chat/response/delete.h
#        chat/response/post_message.cpp
#        include/slack/chat/response/post_message.h
#        chat/response/update.cpp
#        include/slack/chat/response/update.h
#        chat/update.cpp
#        include/slack/chat/update.h
#        include/slack/channels/create.h
#        include/slack/channels/impl/create.h
#        include/slack/channels/parameter/create.h
#        include/slack/channels/response/create.h
#        include/slack/channels/response/archive.h
#        channels/create.cpp
#        channels/response/create.cpp
#        channels/impl/create.cpp
#        include/slack/channels/archive.h
#        include/slack/channels/parameter/archive.h
#        include/slack/channels/impl/archive.h
#        channels/archive.cpp
#        channels/impl/archive.cpp
#        channels/response/archive.cpp
#        include/slack/rtm/start.h
#        include/slack/rtm/response/start.h
#        include/slack/rtm/parameter/start.h
#        include/slack/rtm/impl/start.h
#        rtm/start.cpp
#        rtm/impl/start.cpp
#        rtm/parameter/start.cpp
#        rtm/response/start.cpp
#        include/slack/rtm.h
)
add_library(slack STATIC ${JSON_SOURCES} ${SLACK_FILES})

target_link_libraries(slack
        ${OPENSSL_LIBRARIES}
        ${CPR_LIBRARIES}
        curl
        )

#tests
#TODO make this an option.
add_subdirectory(tests)