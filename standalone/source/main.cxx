// A simple program that outputs the square root of a number
#include <fmt/core.h>
#include <mathfunctions/Addition.h>
#include <mathfunctions/SquareRoot.h>

#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int {
  if (argc < 2) {
    std::cerr << "Usage: " << *argv << " number" << std::endl;
    return 1;
  }

  // convert input to double
  const double inputValue = std::stod(argv[1]);

  // calculate square root
  const double sqrt = MathFunctions::sqrt(inputValue);
  fmt::print("The square root of {} is {}\n", inputValue, sqrt);

  // calculate sum
  const double sum = MathFunctions::add(inputValue, inputValue);
  fmt::print("{0} + {0} = {1}\n", inputValue, sum);

  return 0;
}
