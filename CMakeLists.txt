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
        )


set(SLACK_FILES
        include/slack/slack.h
        config.cpp
        config.h
        include/slack/config.h
        types.cpp
        include/slack/types.h
        include/slack/response/base.h
        include/slack/api/impl/test.h
        include/slack/api/parameter/test.h
        include/slack/api/response/test.h
        include/slack/api/test.h
        include/slack/auth/impl/test.h
        include/slack/auth/parameter/test.h
        include/slack/auth/response/test.h
        include/slack/auth/test.h
        include/slack/channels/delete.h
        include/slack/channels/impl/delete.h
        include/slack/channels/impl/post_message.h
        include/slack/channels/impl/update.h
        include/slack/channels/parameter/delete.h
        channels/parameter/list.cpp
        include/slack/channels/parameter/post_message.h
        include/slack/channels/parameter/update.h
        include/slack/channels/post_message.h
        include/slack/channels/response/delete.h
        channels/response/list.cpp
        include/slack/channels/response/post_message.h
        include/slack/channels/response/update.h
        include/slack/channels/update.h
        chat/delete.cpp
        chat/impl/delete.cpp
        include/slack/chat/impl/list.h
        chat/impl/post_message.cpp
        chat/impl/update.cpp
        include/slack/chat/list.h
        chat/parameter/delete.cpp
        include/slack/chat/parameter/list.h
        chat/parameter/post_message.cpp
        chat/parameter/update.cpp
        chat/post_message.cpp
        chat/response/delete.cpp
        include/slack/chat/response/list.h
        chat/response/post_message.cpp
        chat/response/update.cpp
        chat/update.cpp
        main.cpp
        )
add_library(slack STATIC ${JSON_SOURCES} ${SLACK_FILES})

target_link_libraries(slack
        ${OPENSSL_LIBRARIES}
        ${CPR_LIBRARIES}
        curl
        )

#tests

set(SOURCE_FILES main.cpp)
add_executable(slack_tests ${SOURCE_FILES})

target_link_libraries(slack_tests
        slack
        )