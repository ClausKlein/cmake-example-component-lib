// A simple program that outputs the square root of a number
#include <mathfunctions/Addition.h>
#include <mathfunctions/SquareRoot.h>

#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  const double inputValue = std::stod(argv[1]);

  // calculate square root
  const double sqrt = MathFunctions::sqrt(inputValue);
  std::cout << "The square root of " << inputValue << " is " << sqrt << std::endl;

  // calculate sum
  const double sum = MathFunctions::add(inputValue, inputValue);
  std::cout << inputValue << " + " << inputValue << " = " << sum << std::endl;

  return 0;
}
