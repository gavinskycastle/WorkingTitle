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
        
        Platform* platform;
        PlayerState state;
        
        Vector2 leftArmOrigin = Vector2{0, 0};
        Vector2 rightArmOrigin = Vector2{100, 0};
        
        Vector2 leftLegOrigin = Vector2{35, 30};
        Vector2 rightLegOrigin = Vector2{70, 30};
        
        LimbFrame standingFrame = LimbFrame{
            Vector2{-50, 5}, // Left arm
            Vector2{150, 10}, // Right arm
            Vector2{35, 80}, // Left leg 1
            Vector2{45, 80}, // Left leg 2
            Vector2{70, 80}, // Right leg 1
            Vector2{80, 80}, // Right leg 2
        };
        
        LimbFrame testFrame = LimbFrame{
            Vector2{-50-50, 5}, // Left arm
            Vector2{150+50, 10}, // Right arm
            Vector2{35-50, 80+50}, // Left leg 1
            Vector2{45-50, 80+50}, // Left leg 2
            Vector2{70+50, 80+50}, // Right leg 1
            Vector2{80+50, 80+50}, // Right leg 2
        };
        
        LimbFrame walkFrame1 = LimbFrame{};
        LimbFrame walkFrame2 = LimbFrame{};
        LimbFrame walkFrame3 = LimbFrame{};
        LimbFrame walkFrame4 = LimbFrame{};
        
        // Animation stuff
        void moveToFrame(LimbFrame frame, float seconds);
        
        bool frameFinished = true;
        float timeToNextFrame = 0;
        float timeSinceFrameStart = 0;
        
        LimbFrame originalFrame = standingFrame;
        LimbFrame finalFrame = standingFrame;
        
        Vector2 leftArm;
        Vector2 rightArm;
        Vector2 leftLegLimb1;
        Vector2 leftLegLimb2;
        Vector2 rightLegLimb1;
        Vector2 rightLegLimb2;
};

#endif // PLAYER_H