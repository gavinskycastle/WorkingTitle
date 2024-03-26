#include "../libs/raylib/src/raylib.h"
#include "../libs/raylib/src/raymath.h"
#include "math.hpp"
#include "platform.hpp"
#include <vector>
#include <iostream>

Platform::Platform(int x, int y, int width, int height, Color border_color, Color fill_color, float angle, int line_thickness, bool is_ground, bool use_old_rendering) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->init_angle = angle;
    this->angle = angle;
    this->line_thickness = line_thickness;
    this->is_ground = is_ground;
    this->rotation = INDEPENDENT;
    this->use_old_rendering = use_old_rendering;
}

Platform::Platform(int x, int y, int width, int height, Color border_color, Color fill_color, float angle, int line_thickness, bool is_ground) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->init_angle = angle;
    this->angle = angle;
    this->line_thickness = line_thickness;
    this->is_ground = is_ground;
    this->rotation = INDEPENDENT;
    this->use_old_rendering = false;
}

void Platform::attach(Platform *platform, PlatformRotation rotation) {
    this->parent = platform;
    this->rotation = rotation;
}

void Platform::detach() {
    this->parent = nullptr;
    this->rotation = INDEPENDENT;
}

void Platform::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Platform::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;
}

void Platform::enlarge(int dw, int dh) {
    this->width += dw;
    this->height += dh;
}

void Platform::scale(int wm, int hm) {
    this->width *= wm;
    this->height *= hm;
}

void Platform::draw() {
    if (this->use_old_rendering) {
        DrawRectanglePro(Rectangle{static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->width), static_cast<float>(this->height)},
            Vector2{static_cast<float>(this->height/2), static_cast<float>(this->width/2)}, this->angle, this->border_color);
        if (!this->is_ground)
            DrawRectanglePro(Rectangle{static_cast<float>(this->x) + static_cast<float>(this->line_thickness), static_cast<float>(this->y) + static_cast<float>(this->line_thickness), static_cast<float>(this->width - this->line_thickness*2), static_cast<float>(this->height - this->line_thickness*2)},
                Vector2{static_cast<float>(this->height/2), static_cast<float>(this->width/2)}, this->angle, this->fill_color);
    } else {
        DrawRectangle(static_cast<int>(this->x), static_cast<int>(this->y), static_cast<int>(this->width), static_cast<int>(this->height), this->border_color);
        if (!this->is_ground)
            DrawRectangle(static_cast<int>(this->x) + this->line_thickness, static_cast<int>(this->y) + this->line_thickness, static_cast<int>(this->width - this->line_thickness*2), static_cast<int>(this->height - this->line_thickness*2), this->fill_color);
    }
}
