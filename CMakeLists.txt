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
        include/slack/channels.archive.h channels.archive.cpp)

add_library(slack STATIC ${JSON_SOURCES} ${SLACK_FILES})

#tests
#TODO make this an option.
add_subdirectory(tests)