#include <math.h>
#include "radians.h"

float toRadians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

float toDegrees(float radians) {
    return radians * (180.0f / M_PI);
}
