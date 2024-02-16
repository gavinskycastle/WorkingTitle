#ifndef PLAYER_H
#define PLAYER_H

#include "../libs/raylib/src/raylib.h"
#include "platform.hpp"

enum PlayerState {
    CROUCHING,
    STANDING,
    WALKING,
    RUNNING,
    TIPOVER
};

struct LimbFrame {
    Vector2 leftArm;
    Vector2 rightArm;
    Vector2 leftLegLimb1;
    Vector2 leftLegLimb2;
    Vector2 rightLegLimb1;
    Vector2 rightLegLimb2;
};

class Player {
    public:
        Player(int x, int y, Color border_color, Color fill_color);
        void setPosition(int x, int y);
        void move(int dx, int dy);
        void draw();
    
    private:
        float x;
        float y;
        float gravity;
        Color border_color;
        Color fill_color;
        
        Vector2 leftArmOrigin = Vector2{0, 0};
        Vector2 rightArmOrigin = Vector2{100, 0};
        
        Vector2 leftLegOrigin = Vector2{35, 30};
        Vector2 rightLegOrigin = Vector2{70, 30};
        
        LimbFrame walkFrame1 = LimbFrame{};
        LimbFrame walkFrame2 = LimbFrame{};
        LimbFrame walkFrame3 = LimbFrame{};
        LimbFrame walkFrame4 = LimbFrame{};
        
        Platform* platform;
        PlayerState state;
};

#endif // PLAYER_H