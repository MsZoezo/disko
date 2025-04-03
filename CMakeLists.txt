cmake_minimum_required(VERSION 3.28)

project(disko VERSION 1.0)

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
src/main.cpp
src/config.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt)
target_include_directories(${PROJECT_NAME} PRIVATE ${tomlplusplus_SOURCE_DIR}/include include)

set_target_properties(${PROJECT_NAME} PROPERTIES
CXX_STANDARD 20
CXX_STANDARD_REQUIRED ON
)