#pragma once

// quickhack for now! CK
#ifdef Addition_EXPORTS
#  define MathFunctions_EXPORTS
#endif

#include <mathfunctions/mathfunctions_export.h>

namespace MathFunctions {
  double MATHFUNCTIONS_EXPORT add(double x, double y);
}
