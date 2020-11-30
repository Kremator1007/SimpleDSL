cmake_minimum_required(VERSION 3.16)

project(DSL)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_CLANG_TIDY 
#   clang-tidy;
#   -checks=*)
add_subdirectory(dsllib)
enable_testing()
add_subdirectory(tests)

