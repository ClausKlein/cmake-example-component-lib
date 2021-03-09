#include <mathfunctions/Addition.h>
#include <mathfunctions/SquareRoot.h>

// import boost.ut;        // single module (C++20)
#include <boost/ut.hpp>  // single header

auto main() -> int {
  using namespace boost::ut;

  // calculate square root
  expect(1.41421356_d == MathFunctions::sqrt(2.0));
  expect(2.0 == MathFunctions::sqrt(4.0));
  expect(3.0 == MathFunctions::sqrt(9.0));
  expect(2.23606797_d == MathFunctions::sqrt(5.0));
  expect(2.64575131_d == MathFunctions::sqrt(7.0));
  expect(5.0_d == MathFunctions::sqrt(25.0));
  expect(0.01_d == MathFunctions::sqrt(0.0001));
  expect(isnan(MathFunctions::sqrt(-25.0)));

  // calculate sum
  expect(2.0_d == MathFunctions::add(1.0, 1.0));
  expect(0.0_d == MathFunctions::add(-1.0, 1.0));
  expect(0.2_d == MathFunctions::add(0.1, 0.1));
}
