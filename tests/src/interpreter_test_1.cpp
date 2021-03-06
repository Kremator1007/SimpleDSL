#include <iostream>
#include <stdexcept>
#include <string>

#include "interpreter.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

TEST_CASE("Casual working") {
	simplelang::Interpreter interpreter{};
	int ans = -1;
	auto addLambda = [&ans](int a, int b) { ans = a + b; };
	auto subtractLambda = [&ans](int a, int b) { ans = a - b; };
	interpreter.addCommand<int, int>(std::string{"add"}, addLambda);
	interpreter.addCommand<int, int>(std::string{"sub"}, subtractLambda);
	interpreter.runCommand("add 2 3");
	CHECK(ans == 5);
	interpreter.runCommand("  add  2  8  ");
	CHECK(ans == 10);
}

TEST_CASE("Parameter amount overloading") {
	simplelang::Interpreter interpreter{};
	int ans = -1;
	auto add2Lambda = [&ans](int a, int b) { ans = a + b; };
	auto add3Lambda = [&ans](int a, int b, int c) { ans = a + b + c; };
	interpreter.addCommand<int, int>(std::string{"add"}, add2Lambda);
	interpreter.addCommand<int, int, int>(std::string{"add"}, add3Lambda);
	interpreter.runCommand("add 2 3");
	CHECK(ans == 5);
	interpreter.runCommand("add 20 30 40");
	CHECK(ans == 90);
}

TEST_CASE("Dealing with ill-formed commands") {
	simplelang::Interpreter interpreter{};
	interpreter.addCommand<int>("ok", [](int) {});
	interpreter.addCommand<float>("ok", [](float) {});
	simplelang::CommandIntepretingState res = interpreter.runCommand("ok 7");
	CHECK(res == simplelang::CommandIntepretingState::ambigouousCall);
}

TEST_CASE("Various parameter type overload") {
	simplelang::Interpreter interpreter{};
	int ans = -1;
	auto dummyInt = [&ans](int) { ans = 0; };
	auto dummyChar = [&ans](char) { ans = 1; };
	interpreter.addCommand<int>(std::string{"dummy"}, dummyInt);
	interpreter.addCommand<char>(std::string{"dummy"}, dummyChar);
	interpreter.runCommand("dummy 34");
	CHECK(ans == 0);
	interpreter.runCommand("dummy u");
	CHECK(ans == 1);
}