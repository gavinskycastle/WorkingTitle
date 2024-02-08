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
};

#endif // PLAYER_H