cmake_minimum_required(VERSION 3.20)
project(logistics_greedy_router)

include(GoogleTest)
enable_testing()

add_library(${PROJECT_NAME} STATIC
    src/distribution/distribution.cpp
    src/file_io/file_io.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    src/distribution
    src/file_io
)

add_executable(cargo_app src/main.cpp)
target_link_libraries(cargo_app PRIVATE ${PROJECT_NAME})

add_subdirectory(extern/googletest-main)

add_executable(test_distribution tests/test_distribution.cpp)
target_link_libraries(test_distribution
    PRIVATE
    ${PROJECT_NAME}
    gtest_main
)

gtest_discover_tests(test_distribution)