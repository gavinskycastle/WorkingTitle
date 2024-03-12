#ifndef MENU_H
#define MENU_H

#include "../libs/raylib/src/raylib.h"

struct MenuState {
    int selectedLevel;
    bool exit;
};

class Menu {
    public:
        Menu(Color borderColor, Color fillColor, Color textColor);
        // Returns whether the window should close or not
        MenuState draw();
        void close();
    
    private:
        Color borderColor;
        Color fillColor;
        Color textColor;
        
        Texture2D logoTexture;
        
        int selectedLevel = 0;
};

#endif // MENU_H