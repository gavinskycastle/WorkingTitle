#ifndef PICKUP_H
#define PICKUP_H

#include <string>
#include "../libs/raylib/src/raylib.h"

class Pickup {
    public:
        Pickup(int x, int y, std::string label, bool attachedToPlayer, bool isFilled, Texture2D* blankPickupTexture, Font* serifFont);
        void draw();
        void empty();
        void fill(std::string label);
        Rectangle getRect();
        std::string getLabel();
        void setPosition(int x, int y);
        
        int x;
        int y;
        
        bool isFilled;
        
        Texture2D* blankPickupTexture;
        Font* serifFont;
    
    private:
        bool attachedToPlayer;
        std::string label;
        
        Color fillColor = Color{187, 124, 86, 255};
        Color borderColor = Color{71, 35, 11, 255};
};

#endif // PICKUP_H