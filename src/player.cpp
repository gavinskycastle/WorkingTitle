#include "../libs/raylib/src/raylib.h"
#include "player.hpp"
#include "math.hpp"
#include <iostream>

Player::Player(int x, int y, Color border_color, Color fill_color) {
    this->x = x;
    this->y = y;
    this->border_color = border_color;
    this->fill_color = fill_color;
    
    this->platform = new Platform(16, 45, 100, 35, border_color, fill_color, 0, 5, false);
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

void Player::draw(std::vector<Pickup*> pickup) {
    bool flipTexture = false;
    
    BeginTextureMode(drawTexture);        
        ClearBackground(BLANK);
        
        float dx = 0;
        
        // Draw eyes
        DrawCircle(sTPtextureX((100/2)-15), sTPtextureY(-(35/2)), 10, WHITE);
        DrawCircle(sTPtextureX((100/2)+15), sTPtextureY(-(35/2)), 10, WHITE);
        
        // Jump key press detection
        if (IsKeyPressed(KEY_W) && this->gravity == 0) {
            this->gravity = -10;
            bool justJumped = true;
        }
        
        // Left and right movement key press detection
        if (IsKeyDown(KEY_A)) {
            if (IsKeyDown(KEY_LEFT_SHIFT))
                dx -= 10;
            else
                dx -= 5;
            flipTexture = true;
            DrawCircle(sTPtextureX((100/2)-15+3), sTPtextureY(-(35/2)), 5, BLACK);
            DrawCircle(sTPtextureX((100/2)+15+3), sTPtextureY(-(35/2)), 5, BLACK);
        }
        else if (IsKeyDown(KEY_D)) {
            if (IsKeyDown(KEY_LEFT_SHIFT))
                dx += 10;
            else
                dx += 5;
            DrawCircle(sTPtextureX((100/2)-15+3), sTPtextureY(-(35/2)), 5, BLACK);
            DrawCircle(sTPtextureX((100/2)+15+3), sTPtextureY(-(35/2)), 5, BLACK);
        }
        else {
            DrawCircle(sTPtextureX((100/2)-15), sTPtextureY(-(35/2)), 5, BLACK);
            DrawCircle(sTPtextureX((100/2)+15), sTPtextureY(-(35/2)), 5, BLACK);
        }
        
        // Gravity decceleartion/acceleration
        this->gravity += 0.5;
        
        // Gravity limit
        if (this->gravity > 10) {
            this->gravity = 10;
        }
        
        // Gravity application
        this->y += this->gravity;
        
        // Movement application
        this->x += dx;
        
        // Ground detection
        if (this->y >= 500) {
            this->y = 500;
            this->gravity = 0;
            
        }
        
        // Animation frame update
        if (this->timeSinceFrameStart > this->timeToNextFrame) {
            this->frameFinished = true;
        }
        
        if (dx == 0) {
            this->moveToFrame(this->standingFrame, 0.08);
        } else if (this->finalFrame.id == this->standingFrame.id && this->frameFinished) {
            this->moveToFrame(this->walkFrame1, 0.08);
        } else if (this->finalFrame.id == this->walkFrame1.id && this->frameFinished) {
            this->moveToFrame(this->walkFrame2, 0.08);
        } else if (this->finalFrame.id == this->walkFrame2.id && this->frameFinished) {
            this->moveToFrame(this->walkFrame3, 0.08);
        } else if (this->finalFrame.id == this->walkFrame3.id && this->frameFinished) {
            this->moveToFrame(this->walkFrame4, 0.08);
        } else if (this->finalFrame.id == this->walkFrame4.id && this->frameFinished) {
            this->moveToFrame(this->walkFrame1, 0.08);
        }
        
        if (this->frameFinished) {
            this->leftArm = finalFrame.leftArm;
            this->rightArm = finalFrame.rightArm;
            this->leftLegLimb1 = finalFrame.leftLegLimb1;
            this->leftLegLimb2 = finalFrame.leftLegLimb2;
            this->leftLegLimb3 = finalFrame.leftLegLimb3;
            this->rightLegLimb1 = finalFrame.rightLegLimb1;
            this->rightLegLimb2 = finalFrame.rightLegLimb2;
            this->rightLegLimb3 = finalFrame.rightLegLimb3;
        } else {
            this->timeSinceFrameStart += GetFrameTime();
            
            if (this->holdingPickup) {
                this->leftArm = Vector2{15, 47}; // Left arm
                this->rightArm = Vector2{85, 47}; // Right arm
                this->pickupBeingHeld->draw();
            } else {
                this->leftArm = vectorLerp(this->originalFrame.leftArm, finalFrame.leftArm, this->timeSinceFrameStart/this->timeToNextFrame);
                this->rightArm = vectorLerp(this->originalFrame.rightArm, finalFrame.rightArm, this->timeSinceFrameStart/this->timeToNextFrame);
            }
            this->leftLegLimb1 = vectorLerp(this->originalFrame.leftLegLimb1, finalFrame.leftLegLimb1, this->timeSinceFrameStart/this->timeToNextFrame);
            this->leftLegLimb2 = vectorLerp(this->originalFrame.leftLegLimb2, finalFrame.leftLegLimb2, this->timeSinceFrameStart/this->timeToNextFrame);
            this->leftLegLimb3 = vectorLerp(this->originalFrame.leftLegLimb3, finalFrame.leftLegLimb3, this->timeSinceFrameStart/this->timeToNextFrame);
            this->rightLegLimb1 = vectorLerp(this->originalFrame.rightLegLimb1, finalFrame.rightLegLimb1, this->timeSinceFrameStart/this->timeToNextFrame);
            this->rightLegLimb2 = vectorLerp(this->originalFrame.rightLegLimb2, finalFrame.rightLegLimb2, this->timeSinceFrameStart/this->timeToNextFrame);
            this->rightLegLimb3 = vectorLerp(this->originalFrame.rightLegLimb3, finalFrame.rightLegLimb3, this->timeSinceFrameStart/this->timeToNextFrame);
        }
        
        // Draw platform
        this->platform->setPosition(70, 120);
        this->platform->draw();
        
        // Draw limbs
        DrawLineEx(sTPvector2({leftArmOrigin.x, leftArmOrigin.y}), sTPvector2({leftArm.x, leftArm.y}), 7, WHITE); // Left arm
        DrawLineEx(sTPvector2({rightArmOrigin.x, rightArmOrigin.y}), sTPvector2({rightArm.x, rightArm.y}), 7, WHITE); // Right arm
        DrawLineEx(sTPvector2({leftLegOrigin.x, leftLegOrigin.y}), sTPvector2({leftLegLimb1.x, leftLegLimb1.y}), 7, WHITE); // Left leg 1
        DrawLineEx(sTPvector2({leftLegLimb1.x, leftLegLimb1.y}), sTPvector2({leftLegLimb2.x, leftLegLimb2.y}), 7, WHITE); // Left leg 2
        DrawLineEx(sTPvector2({leftLegLimb2.x, leftLegLimb2.y}), sTPvector2({leftLegLimb3.x, leftLegLimb3.y}), 7, WHITE); // Left leg 3
        DrawLineEx(sTPvector2({rightLegOrigin.x, rightLegOrigin.y}), sTPvector2({rightLegLimb1.x, rightLegLimb1.y}), 7, WHITE); // Right leg 1
        DrawLineEx(sTPvector2({rightLegLimb1.x, rightLegLimb1.y}), sTPvector2({rightLegLimb2.x, rightLegLimb2.y}), 7, WHITE); // Right leg 2
        DrawLineEx(sTPvector2({rightLegLimb2.x, rightLegLimb2.y}), sTPvector2({rightLegLimb3.x, rightLegLimb3.y}), 7, WHITE); // Right leg 3
    EndTextureMode();
        
    if (flipTexture) {
        DrawTextureRec(drawTexture.texture, Rectangle{0, 0, static_cast<float>(-drawTexture.texture.width), static_cast<float>(drawTexture.texture.height)}, Vector2{x-60, y-40}, WHITE);
    } else {
        DrawTexture(drawTexture.texture, x-60, y-40, WHITE);
    }
    
    Rectangle playerRect = Rectangle{x, y, 100, 100};
    
    // Check if the key E has just been pressed
    if (IsKeyPressed(KEY_E)) {
        // Find the first, if any, pickup that the player is touching
        for (int i = 0; i < pickup.size(); i++) {
            if (CheckCollisionRecs(playerRect, pickup[i]->getRect())) {
                if (this->holdingPickup) {
                    pickup[i]->fill(this->pickupBeingHeld->getLabel());
                    this->pickupBeingHeld = nullptr;
                    this->holdingPickup = false;
                } else {
                    this->pickupBeingHeld = new Pickup(pickup[i]->x, pickup[i]->y, pickup[i]->getLabel(), true);
                    this->holdingPickup = true;
                }
                break;
            }
        }
    }
}

void Player::close() {
    UnloadRenderTexture(drawTexture);
}