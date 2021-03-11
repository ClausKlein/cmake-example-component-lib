#pragma once

// quickhack for now! CK
#ifdef SquareRoot_EXPORTS
#  define MathFunctions_EXPORTS
#endif

#include <mathfunctions/mathfunctions_export.h>

namespace MathFunctions {
  double MATHFUNCTIONS_EXPORT sqrt(double x);
}
