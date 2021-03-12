#pragma once

#include <mathfunctions/mathfunctions_export.h>

namespace MathFunctions {
  double MATHFUNCTIONS_EXPORT sqrt(double x);

  auto inline add(double x, double y) -> double { return x + y; }
  auto inline dif(double x, double y) -> double { return x - y; }
  auto inline mul(double x, double y) -> double { return x * y; }
  auto inline quo(double x, double y) -> double { return x / y; }
}  // namespace MathFunctions
