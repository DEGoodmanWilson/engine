cmake_minimum_required(VERSION 2.8)

enable_testing()

set(ENGINE_TEST_FILES
        main.cpp
        types.cpp
        api.cpp
#        auth.cpp
#        channels.cpp
#        chat.cpp
#        oauth.cpp
#        rtm.cpp
        environment.h)

add_executable(engine_tests ${ENGINE_TEST_FILES})

target_link_libraries(engine_tests
        ${CONAN_LIBS}
        engine
        )

add_test(engine ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/engine_tests)