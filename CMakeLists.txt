cmake_minimum_required(VERSION 3.12)
project(medusa VERSION 1.0)

file(GLOB_RECURSE SRC_FILES "src/*.cxx")

add_library(medusa ${SRC_FILES})
add_subdirectory(example)

target_include_directories(medusa PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(medusa PUBLIC cxx_std_20)
