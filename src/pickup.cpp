#include "pickup.hpp"
#include "../libs/raylib/src/raylib.h"
#include "math.hpp"

Pickup::Pickup(int x, int y, std::string label) {
    this->x = x;
    this->y = y;
    this->isFilled = true;
    this->label = label;
}

void Pickup::draw() {
    if (this->isFilled) {
        DrawTexture(blankPickupTexture, this->x, this->y, WHITE);
        DrawCircle(this->x+35, this->y+35, 35, this->borderColor);
        DrawCircle(this->x+35, this->y+35, 30, this->fillColor);
        DrawTextCentered(this->label.c_str(), this->x+35, this->y+35, 35, BLACK);
    }
}