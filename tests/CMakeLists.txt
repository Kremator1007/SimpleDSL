cmake_minimum_required(VERSION 3.0.0)


find_package(doctest REQUIRED)
if(doctest_FOUND)
    message("Found doctest")
endif()

add_executable(interpreter_test_1_ src/interpreter_test_1.cpp)
target_link_libraries(interpreter_test_1_  dsllib  doctest::doctest)
add_test(interpreter_test_1 interpreter_test_1_)