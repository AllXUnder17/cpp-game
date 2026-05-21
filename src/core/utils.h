#ifndef _UTILS_
#define _UTILS_

#include <raymath.h>

namespace utils {
    float RoundToDigit(const float& value, const unsigned short& digits);
    Vector2 RoundToDigit(const Vector2& value, const unsigned short& digits);
} // namespace utils

#endif