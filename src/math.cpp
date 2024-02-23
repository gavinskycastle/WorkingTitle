#include <cmath>
#include "../libs/raylib/src/raylib.h"
#include "../libs/raylib/src/rlgl.h"
#include "../libs/raylib/src/raymath.h"

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

// Draw textured polygon, defined by vertex and texture coordinates
// NOTE: Polygon center must have straight line path to all points
// without crossing perimeter, points must be in anticlockwise order
void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointCount, Color tint)
{
    rlSetTexture(texture.id);

    // Texturing is only supported on RL_QUADS
    rlBegin(RL_QUADS);

        rlColor4ub(tint.r, tint.g, tint.b, tint.a);

        for (int i = 0; i < pointCount - 1; i++)
        {
            rlTexCoord2f(0.5f, 0.5f);
            rlVertex2f(center.x, center.y);

            rlTexCoord2f(texcoords[i].x, texcoords[i].y);
            rlVertex2f(points[i].x + center.x, points[i].y + center.y);

            rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
            rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);

            rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
            rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
        }
    rlEnd();

    rlSetTexture(0);
}

// Calculate linear interpolation between two Vector2Ds
Vector2 vectorLerp(Vector2 a, Vector2 b, float t) {
    return Vector2{Lerp(a.x, b.x, t), Lerp(a.y, b.y, t)};
}