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
    int id;
    Vector2 leftArm;
    Vector2 rightArm;
    Vector2 leftLegLimb1;
    Vector2 leftLegLimb2;
    Vector2 leftLegLimb3;
    Vector2 rightLegLimb1;
    Vector2 rightLegLimb2;
    Vector2 rightLegLimb3;
};

class Player {
    public:
        Player(int x, int y, Color border_color, Color fill_color);
        void setPosition(int x, int y);
        void move(int dx, int dy);
        void draw();
        void close();
    
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
            0, // ID
            Vector2{-50, 5}, // Left arm
            Vector2{150, 10}, // Right arm
            Vector2{35, 70}, // Left leg 1
            Vector2{35, 80}, // Left leg 2
            Vector2{45, 80}, // Left leg 3
            Vector2{70, 70}, // Right leg 1
            Vector2{70, 80}, // Right leg 2
            Vector2{80, 80}, // Right leg 3
        };
        
        LimbFrame testFrame = LimbFrame{
            1, // ID
            Vector2{-50-50, 5}, // Left arm
            Vector2{150+50, 10}, // Right arm
            Vector2{35-50, 80+40}, // Left leg 1
            Vector2{35-50, 80+50}, // Left leg 2
            Vector2{45-50, 80+50}, // Left leg 3
            Vector2{70+50, 80+40}, // Right leg 1
            Vector2{70+50, 80+50}, // Right leg 2
            Vector2{80+50, 80+50}, // Right leg 3
        };
        
        LimbFrame walkFrame1 = LimbFrame{
            2, // ID
            Vector2{-50, 20}, // Left arm
            Vector2{150, -4}, // Right arm
            Vector2{19, 51}, // Left leg 1
            Vector2{-5, 72}, // Left leg 2
            Vector2{23, 91}, // Left leg 3
            Vector2{85, 59}, // Right leg 1
            Vector2{100, 82}, // Right leg 2
            Vector2{127, 65}, // Right leg 3
        };
        
        LimbFrame walkFrame2 = LimbFrame{
            3, // ID
            Vector2{47, 21}, // Left arm
            Vector2{144, 25}, // Right arm
            Vector2{20, 62}, // Left leg 1
            Vector2{-6, 73}, // Left leg 2
            Vector2{-1, 94}, // Left leg 3
            Vector2{101, 48}, // Right leg 1
            Vector2{91, 94}, // Right leg 2
            Vector2{120, 88}, // Right leg 3
        };
        
        LimbFrame walkFrame3 = LimbFrame{
            4, // ID
            Vector2{-21, 54}, // Left arm
            Vector2{116, 56}, // Right arm
            Vector2{42, 62}, // Left leg 1
            Vector2{42, 92}, // Left leg 2
            Vector2{66, 94}, // Left leg 3
            Vector2{70, 58}, // Right leg 1
            Vector2{17, 66}, // Right leg 2
            Vector2{18, 82}, // Right leg 3
        };
        
        LimbFrame walkFrame4 = LimbFrame{
            5, // ID
            Vector2{-19, 52}, // Left arm
            Vector2{94, 58}, // Right arm
            Vector2{31, 55}, // Left leg 1
            Vector2{22, 75}, // Left leg 2
            Vector2{44, 89}, // Left leg 3
            Vector2{92, 55}, // Right leg 1
            Vector2{71, 72}, // Right leg 2
            Vector2{80, 92}, // Right leg 3
        };
        
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
        Vector2 leftLegLimb3;
        Vector2 rightLegLimb1;
        Vector2 rightLegLimb2;
        Vector2 rightLegLimb3;
        
        RenderTexture2D drawTexture = LoadRenderTexture(220, 140);
};

#endif // PLAYER_H