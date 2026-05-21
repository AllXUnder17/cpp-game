#include "utils.h"

#include <cmath>

float utils::RoundToDigit(const float& value, const unsigned short& digits) {
    float p = pow(10, digits);
    return round(value * p) / p;
}

Vector2 utils::RoundToDigit(const Vector2& value, const unsigned short& digits) {
    Vector2 v = value;

    v.x = RoundToDigit(v.x, digits);
    v.y = RoundToDigit(v.y, digits);

    return v;
}