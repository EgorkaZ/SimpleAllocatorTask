cmake_minimum_required(VERSION 3.15)

project(SimpleAllocTask)

file(GLOB sources "src/*.cpp")

add_executable(SimpleAllocTaskExe "${sources}")

target_include_directories(SimpleAllocTaskExe PUBLIC "include")

target_compile_features(SimpleAllocTaskExe PUBLIC cxx_std_17)
