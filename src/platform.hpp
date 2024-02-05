#ifndef PLATFORM_H
#define PLATFORM_H

#include "../libs/raylib/src/raylib.h"
#include "../libs/raylib/src/raymath.h"
#include "math.hpp"
#include <vector>

enum PlatformRotation {
    INDEPENDENT,
    FIXED,
    ADDITIVE
};

class Platform {
    public:
        Platform(int x, int y, int width, int height, Color border_color, Color fill_color, float angle, int line_thickness);
        void attach(Platform *platform, PlatformRotation rotation);
        void detach();
        // void rotate(int degrees);
        void move(int dx, int dy);
        void enlarge(int dw, int dh);
        void scale(int wm, int hm);
        // void updateAngle();
        // std::vector<Vector2> getOuterPoints();
        // std::vector<Vector2> getInnerPoints();
        // Vector2 getCenterPoint();
        // Vector2 getEndPosition();
        void draw();

    private:
        int x;
        int y;
        int width;
        int height;
        Color border_color;
        Color fill_color;
        float init_angle;
        float angle;
        int line_thickness;
        PlatformRotation rotation;
        Platform *parent;
        Texture2D border_color_texture;
        Texture2D fill_color_texture;
        // std::vector<Vector2> getOuterPoints(bool rotate);
        // std::vector<Vector2> getInnerPoints(std::vector<Vector2> outer_points, bool rotate = true);
};

#endif // PLATFORM_H