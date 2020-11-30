#include "trim.h"

#include <iostream>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

TEST_CASE("Trim test") {
	CHECK(trim("  ad  ") == std::string("ad"));
	CHECK(trim("  ad") == std::string("ad"));
	CHECK(trim("ad  ") == std::string("ad"));
}
