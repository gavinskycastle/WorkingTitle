#ifndef MENU_H
#define MENU_H

#include "../libs/raylib/src/raylib.h"

class Menu {
    public:
        Menu(Color borderColor, Color fillColor, Color textColor);
        void draw();
        void close();
    
    private:
        Color borderColor;
        Color fillColor;
        Color textColor;
        
        Texture2D logoTexture;
};

#endif // MENU_H