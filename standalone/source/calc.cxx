//
// A very simple calculator
//
#include <fmt/core.h>
#include <mathfunctions/MathFunctions.h>

#include <exception>
#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int {
  if (argc < 2) {
    fmt::print(stderr, "Usage: {} number\n", *argv);
    return 0;  // Note: not an error, just a hint ;-)
  }

  // convert input to double
  double inputValue{1.0};
  try {
    inputValue = std::stod(argv[1]);  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  } catch (const std::exception& e) {
    fmt::print(stderr, "Oops: {}; this is not valid number: {}!\n", e.what(), argv[1]);
    return 0;
  }

  // calculate square root
  const double sqrt = MathFunctions::sqrt(inputValue);
  fmt::print("The square root of {} is {}\n", inputValue, sqrt);

  // calculate sum
  const double sum = MathFunctions::add(inputValue, inputValue);
  fmt::print("{0} + {0} = {1}\n", inputValue, sum);

  // calculate difference
  const double dif = MathFunctions::dif(inputValue, inputValue);
  fmt::print("{0} - {0} = {1}\n", inputValue, dif);

  // calculate product
  const double mul = MathFunctions::mul(inputValue, inputValue);
  fmt::print("{0} * {0} = {1}\n", inputValue, mul);

  // calculate quotient
  const double quo = MathFunctions::quo(inputValue, inputValue);
  fmt::print("{0} / {0} = {1}\n", inputValue, quo);

  return 0;
}
