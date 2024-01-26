#include "../libs/raylib/src/raylib.h"

Vector2 rotateVector(Vector2 point, Vector2 origin, float degrees);

void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointCount, Color tint);