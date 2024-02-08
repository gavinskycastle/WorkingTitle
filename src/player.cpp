#include "../libs/raylib/src/raylib.h"
#include "player.hpp"
#include <iostream>

Player::Player(int x, int y, Color border_color, Color fill_color) {
    this->x = x;
    this->y = y;
    this->border_color = border_color;
    this->fill_color = fill_color;
    
    this->platform = new Platform(x, y, 100, 35, border_color, fill_color, 0, 5, false);
}

void Player::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;
}

void Player::draw() {
    
    // Jump key press detection
    if (IsKeyPressed(KEY_W) && this->gravity == 0) {
        this->gravity = -10;
        bool justJumped = true;
    }
    
    // Left and right movement key press detection
    if (IsKeyDown(KEY_A)) {
        if (IsKeyDown(KEY_LEFT_SHIFT))
            this->x -= 10;
        else
            this->x -= 5;
    }
    if (IsKeyDown(KEY_D)) {
        if (IsKeyDown(KEY_LEFT_SHIFT))
            this->x += 10;
        else
            this->x += 5;
    }
    
    // Gravity decceleartion/acceleration
    this->gravity += 0.5;
    
    // Gravity limit
    if (this->gravity > 10) {
        this->gravity = 10;
    }
    
    // Gravity application
    this->y += this->gravity;
    
    // Ground detection
    if (this->y >= 500) {
        this->y = 500;
        this->gravity = 0;
        
    }
    
    DrawCircle(x+(100/2)-15, y-(35/2), 10, WHITE);
    DrawCircle(x+(100/2)+15, y-(35/2), 10, WHITE);

    DrawCircle(x+(100/2)-15+5, y-(35/2), 5, BLACK);
    DrawCircle(x+(100/2)+15+5, y-(35/2), 5, BLACK);

    DrawLineEx(Vector2{x, y}, Vector2{x-50, y+5}, 7, WHITE);
    DrawLineEx(Vector2{x+100, y}, Vector2{x+100+50, y+10}, 7, WHITE);
    
    this->platform->setPosition(this->x, this->y);
    this->platform->draw();
}