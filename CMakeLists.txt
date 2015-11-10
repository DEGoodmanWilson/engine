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
        config.cpp
        config.h
        include/slack/config.h
        auth.cpp
        include/slack/auth.h
        api.cpp
        include/slack/api.h
        chat.cpp
        include/slack/chat.h
        include/slack/types.h
        types.cpp
        include/slack/response/api.h
        include/slack/response/auth.h
        include/slack/response/base.h
        include/slack/slack.h
        include/slack/parameter/api.h include/slack/parameter/base.h)
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