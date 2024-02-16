#include "../libs/raylib/src/raylib.h"
#include "player.hpp"
#include <iostream>

Player::Player(int x, int y, Color border_color, Color fill_color) {
    this->x = x;
    this->y = y;
    this->border_color = border_color;
    this->fill_color = fill_color;
    
    this->platform = new Platform(x+16, y+45, 100, 35, border_color, fill_color, 0, 5, false);
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
    
    DrawCircle(x+(100/2)-15, y-(35/2), 10, WHITE);
    DrawCircle(x+(100/2)+15, y-(35/2), 10, WHITE);
    
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
        DrawCircle(x+(100/2)-15-3, y-(35/2), 5, BLACK);
        DrawCircle(x+(100/2)+15-3, y-(35/2), 5, BLACK);
    }
    else if (IsKeyDown(KEY_D)) {
        if (IsKeyDown(KEY_LEFT_SHIFT))
            this->x += 10;
        else
            this->x += 5;
        DrawCircle(x+(100/2)-15+3, y-(35/2), 5, BLACK);
        DrawCircle(x+(100/2)+15+3, y-(35/2), 5, BLACK);
    }
    else {
        DrawCircle(x+(100/2)-15, y-(35/2), 5, BLACK);
        DrawCircle(x+(100/2)+15, y-(35/2), 5, BLACK);
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

    

    DrawLineEx(Vector2{x, y}, Vector2{x-50, y+5}, 7, WHITE);
    DrawLineEx(Vector2{x+100, y}, Vector2{x+100+50, y+10}, 7, WHITE);
    
    DrawLineEx(Vector2{x+leftLegOrigin.x, y+leftLegOrigin.y}, Vector2{x+35, y+30+50}, 7, WHITE);
    DrawLineEx(Vector2{x+rightLegOrigin.x, y+rightLegOrigin.y}, Vector2{x+70, y+30+50}, 7, WHITE);
    
    this->platform->setPosition(this->x+16, this->y+45);
    this->platform->draw();
}