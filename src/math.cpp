#include <cmath>
#include "../libs/raylib/src/raylib.h"

Vector2 rotateVector(Vector2 point, Vector2 origin, float degrees) {
    double radians = degrees * M_PI / 180.0;
    double adjusted_x, adjusted_y, cos_rad, sin_rad, qx, qy;

    adjusted_x = (point.x - origin.x);
    adjusted_y = (point.y - origin.y);

    cos_rad = cos(radians);
    sin_rad = sin(radians);

    qx = origin.x + cos_rad * adjusted_x + sin_rad * adjusted_y;
    qy = origin.y + -sin_rad * adjusted_x + cos_rad * adjusted_y;

    return {static_cast<float>(qx), static_cast<float>(qy)};
}
