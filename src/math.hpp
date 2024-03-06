#include "../libs/raylib/src/raylib.h"

Vector2 rotateVector(Vector2 point, Vector2 origin, float degrees);

void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointCount, Color tint);

Vector2 vectorLerp(Vector2 a, Vector2 b, float t);

float sTPtextureX(float x);
float sTPtextureY(float y);

Vector2 sTPvector2(Vector2 vector);