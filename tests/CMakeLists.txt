cmake_minimum_required(VERSION 2.8)

set(ENGINE_TEST_FILES main.cpp main.cpp)

add_executable(engine_tests ${ENGINE_TEST_FILES})

target_link_libraries(engine_tests
        ${CONAN_LIBS}
        engine
        )