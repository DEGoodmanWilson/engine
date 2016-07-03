cmake_minimum_required(VERSION 2.8)

set(ENGINE_EXAMPLE_FILES example.cpp)

add_executable(engine_examples ${ENGINE_EXAMPLE_FILES})

target_link_libraries(engine_examples
        ${CONAN_LIBS}
        engine
        )