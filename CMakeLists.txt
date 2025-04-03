cmake_minimum_required(VERSION 3.28)

project(disko VERSION 1.0)

add_executable(${PROJECT_NAME}
src/main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
CXX_STANDARD 20
CXX_STANDARD_REQUIRED ON
)