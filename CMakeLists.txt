cmake_minimum_required(VERSION 3.16.3)

project(stratler VERSION 0.1.0 LANGUAGES C CXX)

set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    engine/pokemon/type/type.cpp
    engine/pokemon/pokemon.cpp
    engine/state/state.cpp
    util/table/table.cpp
)

add_executable(stratler ${SOURCES})