#include "pickup.hpp"
#include "../libs/raylib/src/raylib.h"
#include "math.hpp"

Pickup::Pickup(int x, int y, std::string label, bool attachedToPlayer, bool isFilled) {
    this->x = x;
    this->y = y;
    this->isFilled = isFilled;
    this->label = label;
    this->attachedToPlayer = attachedToPlayer;
}

void Pickup::draw() {
    if (!attachedToPlayer)
        DrawTexture(blankPickupTexture, this->x, this->y, WHITE);
    if (this->isFilled) {
        DrawCircle(this->x+35, this->y+35, 35, this->borderColor);
        DrawCircle(this->x+35, this->y+35, 30, this->fillColor);
        DrawTextCenteredEx(this->label.c_str(), this->x+35, this->y+30, 70, BLACK, serifFont, 1.0f);
    }
}

void Pickup::empty() {
    this->isFilled = false;
    this->label = "";
}

void Pickup::fill(std::string label) {
    this->isFilled = true;
    this->label = label;
}

Rectangle Pickup::getRect() {
    return Rectangle{static_cast<float>(this->x), static_cast<float>(this->y), 70.0f, 70.0f};
}

std::string Pickup::getLabel() {
    return this->label;
}

void Pickup::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}