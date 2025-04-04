cmake_minimum_required(VERSION 3.28)

project(disko VERSION 1.0)

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

find_package(dpp 10.1.2)

if(NOT dpp_FOUND)
    FetchContent_Declare(dpp
        GIT_REPOSITORY https://github.com/brainboxdotcc/DPP
        GIT_TAG v10.1.2
    )

    FetchContent_MakeAvailable(dpp)
endif()

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
src/main.cpp
src/config.cpp
src/logger.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE dpp fmt)
target_include_directories(${PROJECT_NAME} PRIVATE dpp ${tomlplusplus_SOURCE_DIR}/include include)

set_target_properties(${PROJECT_NAME} PROPERTIES
CXX_STANDARD 20
CXX_STANDARD_REQUIRED ON
)