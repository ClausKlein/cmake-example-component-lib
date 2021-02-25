#include <doctest/doctest.h>
#include <greeter/greeter.h>
#include <greeter/version.h>

TEST_CASE("Greeter") {
  using namespace greeter;

  Greeter greeter("Tests");

  CHECK(greeter.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(greeter.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(greeter.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(greeter.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Greeter version") {
#if (__cpp_lib_starts_ends_with)
  static_assert(std::string_view(GREETER_VERSION).starts_with("1"));  // TBD C++20 only
  CHECK(std::string(GREETER_VERSION).starts_with("1"));               // SameMajorVersion
#else
  static_assert(std::string_view(GREETER_VERSION) == std::string_view("1.0.1"));
  CHECK(std::string(GREETER_VERSION) == std::string("1.0.1"));
#endif
}
