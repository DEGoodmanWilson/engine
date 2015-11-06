cmake_minimum_required(VERSION 3.3)
project(plaidapi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#lib

add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS)

# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_COMPONENTS system regex filesystem thread)
find_package(Boost 1.53 REQUIRED ${Boost_COMPONENTS})


# OpenSSL
#set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/1.0.2d_1/)
#find_package(OpenSSL 1.0.2 REQUIRED)
# OpenSSL, because brew.
set(OPENSSL_INCLUDE_DIR /usr/local/Cellar/openssl/1.0.2d_1/include)
set(OPENSSL_LIB_DIR /usr/local/Cellar/openssl/1.0.2d_1/lib)
set(OPENSSL_LIBRARIES ssl crypto)
link_directories(${OPENSSL_LIB_DIR})


# cpp-netlib. Boy wouldn't it be nice to be able to do this in a more system-independent way?
set(CPP_NETLIB_INCLUDE_DIR /usr/local/Cellar/cpp-netlib/0.11.2/include)
set(CPP_NETLIB_LIB_DIR /usr/local/Cellar/cpp-netlib/0.11.2/lib)
link_directories(${CPP_NETLIB_LIB_DIR})

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
)


set(PLAIDAPI_FILES plaid.cpp plaid.h api_base.cpp api_base.h auth.cpp auth.h)
add_library(plaidapi STATIC ${PLAIDAPI_FILES})

target_link_libraries(plaidapi
        cppnetlib-client-connections
        cppnetlib-uri
        curl
        ${OPENSSL_LIBRARIES}
        ${Boost_LIBRARIES}
)

#tests

set(SOURCE_FILES main.cpp)
add_executable(plaidapi_tests ${SOURCE_FILES})

target_link_libraries(plaidapi_tests
        plaidapi
)