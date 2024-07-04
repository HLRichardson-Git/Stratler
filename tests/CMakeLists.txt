cmake_minimum_required(VERSION 3.16.3)

include(GoogleTest)

set (This tests)

set (Sources
    typeTest.cpp
    ${PROJECT_SOURCE_DIR}/engine/pokemon/type/type.cpp
)

add_executable (${This} ${Sources})

target_include_directories(${This} PRIVATE ${PROJECT_SOURCE_DIR}/engine)

target_link_libraries (${This} PRIVATE GTest::gtest_main)

add_test (
    NAME ${This}
    COMMAND ${This}
)

include(GoogleTest)
gtest_discover_tests(${This})