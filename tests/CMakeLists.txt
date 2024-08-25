cmake_minimum_required(VERSION 3.16.3)

include(GoogleTest)

set (This tests)

#set (Sources
#    typeTest.cpp
#    pokemon/stats_calculation/test_stat_calculation.cpp
#    ${PROJECT_SOURCE_DIR}/engine/pokemon/type/type.cpp
#    ${PROJECT_SOURCE_DIR}/engine/state/state.cpp
#)

# Collect all source files from the engine directory
file(GLOB_RECURSE EngineSources 
    ${PROJECT_SOURCE_DIR}/engine/**/*.cpp
)

# Manually list your test sources
set(TestSources
    typeTest.cpp
    pokemon/stats_calculation/test_stat_calculation.cpp
)

# Combine test sources with engine sources
set(Sources
    ${TestSources}
    ${EngineSources}
    ${PROJECT_SOURCE_DIR}/util/table/table.cpp
)

add_executable (${This} ${Sources})

target_include_directories(${This} 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/engine
        ${PROJECT_SOURCE_DIR}/tests
)

target_link_libraries (${This} PRIVATE GTest::gtest_main)

add_test (
    NAME ${This}
    COMMAND ${This}
)

include(GoogleTest)
gtest_discover_tests(${This})