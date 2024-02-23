#include "../libs/raylib/src/raylib.h"
#include "player.hpp"
#include "math.hpp"
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

void Player::moveToFrame(LimbFrame frame, float seconds) {
    this->timeSinceFrameStart = 0;
    this->timeToNextFrame = seconds;
    this->frameFinished = false;
    this->originalFrame = this->finalFrame;
    this->finalFrame = frame;
}

void Player::draw() {
    
    // Draw eyes
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
    
    // Animation frame update
    if (this->timeSinceFrameStart > this->timeToNextFrame) {
        this->frameFinished = true;
    }
    
    if (this->frameFinished) {
        this->leftArm = finalFrame.leftArm;
        this->rightArm = finalFrame.rightArm;
        this->leftLegLimb1 = finalFrame.leftLegLimb1;
        this->leftLegLimb2 = finalFrame.leftLegLimb2;
        this->rightLegLimb1 = finalFrame.rightLegLimb1;
        this->rightLegLimb2 = finalFrame.rightLegLimb2;
    } else {
        this->timeSinceFrameStart += GetFrameTime();
        
        this->leftArm = vectorLerp(this->originalFrame.leftArm, finalFrame.leftArm, this->timeSinceFrameStart/this->timeToNextFrame);
        this->rightArm = vectorLerp(this->originalFrame.rightArm, finalFrame.rightArm, this->timeSinceFrameStart/this->timeToNextFrame);
        this->leftLegLimb1 = vectorLerp(this->originalFrame.leftLegLimb1, finalFrame.leftLegLimb1, this->timeSinceFrameStart/this->timeToNextFrame);
        this->leftLegLimb2 = vectorLerp(this->originalFrame.leftLegLimb2, finalFrame.leftLegLimb2, this->timeSinceFrameStart/this->timeToNextFrame);
        this->rightLegLimb1 = vectorLerp(this->originalFrame.rightLegLimb1, finalFrame.rightLegLimb1, this->timeSinceFrameStart/this->timeToNextFrame);
        this->rightLegLimb2 = vectorLerp(this->originalFrame.rightLegLimb2, finalFrame.rightLegLimb2, this->timeSinceFrameStart/this->timeToNextFrame);
    }
    
    if (IsKeyPressed(KEY_Z)) {
        this->moveToFrame(this->testFrame, 0.5);
    }
    
    // Draw limbs
    DrawLineEx(Vector2{x+leftArmOrigin.x, y+leftArmOrigin.y}, Vector2{x+leftArm.x, y+leftArm.y}, 7, WHITE); // Left arm
    DrawLineEx(Vector2{x+rightArmOrigin.x, y+rightArmOrigin.y}, Vector2{x+rightArm.x, y+rightArm.y}, 7, WHITE); // Right arm
    DrawLineEx(Vector2{x+leftLegOrigin.x, y+leftLegOrigin.y}, Vector2{x+leftLegLimb1.x, y+leftLegLimb1.y}, 7, WHITE); // Left leg 1
    DrawLineEx(Vector2{x+leftLegLimb1.x, y+leftLegLimb1.y}, Vector2{x+leftLegLimb2.x, y+leftLegLimb2.y}, 7, WHITE); // Left leg 2
    DrawLineEx(Vector2{x+rightLegOrigin.x, y+rightLegOrigin.y}, Vector2{x+rightLegLimb1.x, y+rightLegLimb1.y}, 7, WHITE); // Right leg 1
    DrawLineEx(Vector2{x+rightLegLimb1.x, y+rightLegLimb1.y}, Vector2{x+rightLegLimb2.x, y+rightLegLimb2.y}, 7, WHITE); // Right leg 2
    
    // Draw platform
    this->platform->setPosition(this->x+16, this->y+45);
    this->platform->draw();
}