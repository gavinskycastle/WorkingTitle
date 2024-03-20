#ifndef PICKUP_H
#define PICKUP_H

#include <string>
#include "../libs/raylib/src/raylib.h"

class Pickup {
    public:
        Pickup(int x, int y, std::string label);
        void draw();
        void drop(std::string label);
    
    private:
        int x;
        int y;
        bool isFilled;
        std::string label;
        
        Color fillColor = Color{187, 124, 86, 255};
        Color borderColor = Color{71, 35, 11, 255};
        
        Texture2D blankPickupTexture = LoadTextureFromImage(LoadImage("assets/blankPickup.png"));
};

#endif // PICKUP_H