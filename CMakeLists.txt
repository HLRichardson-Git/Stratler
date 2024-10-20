cmake_minimum_required(VERSION 3.16.3)

project(stratler VERSION 0.1.0 LANGUAGES C CXX)

set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

include_directories(
    include
    include/imgui
    include/imgui/backends
)

set(SOURCES
    main.cpp
    engine/pokemon/type/type.cpp
    engine/pokemon/move/move.cpp
    engine/pokemon/nature/nature.cpp
    engine/pokemon/pokemon.cpp
    engine/state/state.cpp
    util/table/table.cpp
)

file(GLOB IMGUI_SOURCES
    "include/imgui/*.cpp"
    "include/imgui/backends/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES}) 
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/data/player_teams
)
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11 d3dcompiler dxguid dwmapi)
#add_executable(${PROJECT_NAME} ${SOURCES})

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#target_link_libraries(stratlerTests PRIVATE gtest_main)
add_subdirectory(tests)