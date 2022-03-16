#define NANOPRINTF_SNPRINTF_SAFE_TRIM_STRING_ON_OVERFLOW
#include "unit_nanoprintf.h"

#include <string>
#include <iostream>

TEST_CASE("snprintf safety: trim string") {
  char buf[9];
  buf[7] = '*';
  buf[8] = '!';

  SUBCASE("small string") {
    REQUIRE(npf_snprintf(buf, 8, "abc") == 3);
    REQUIRE(std::string{buf} == "abc");
  }

  SUBCASE("exact fit string") {
    REQUIRE(npf_snprintf(buf, 8, "1234567") == 7);
    REQUIRE(buf[7] == '\0');
    REQUIRE(std::string{buf} == "1234567");
  }

  SUBCASE("if the null terminator doesn't fit, the string is trimmed") {
    REQUIRE(npf_snprintf(buf, 8, "12345678") == 8);
    REQUIRE(std::string{buf} == "1234567");
    REQUIRE(buf[8] == '!');
  }

  SUBCASE("if the string contents are too long, the string is trimmed") {
    REQUIRE(npf_snprintf(buf, 8, "123456789") == 9);
    REQUIRE(std::string{buf} == "1234567");
    REQUIRE(buf[8] == '!');
  }
}

