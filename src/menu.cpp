#include "menu.hpp"
#include "../libs/raylib/src/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "../libs/raygui/src/raygui.h"

#include <iostream>

Menu::Menu(Color borderColor, Color fillColor, Color textColor) {
    this->borderColor = borderColor;
    this->fillColor = fillColor;
    this->textColor = textColor;
    
    Image logoImage = LoadImage("assets/gameLogo.png");
    ImageResize(&logoImage, logoImage.width/2, logoImage.height/2);
    this->logoTexture = LoadTextureFromImage(logoImage);
};

void Menu::draw() {
    DrawTexture(this->logoTexture, GetScreenWidth()/2 - this->logoTexture.width/2, static_cast<float>(GetScreenHeight())/2-315, WHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(this->fillColor));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(this->textColor));
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(this->borderColor));
    GuiSetStyle(BUTTON, BORDER_WIDTH, 4);
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2-150, 300, 75}, "Play demo level 1") == 1) {
        std::cout << "Play demo level 1" << std::endl;
    };
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2-50, 300, 75}, "Play demo level 2") == 1) {
        std::cout << "Play demo level 2" << std::endl;
    };
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2+50, 300, 75}, "Play demo level 3") == 1) {
        std::cout << "Play demo level 3" << std::endl;
    };
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2+150, 300, 75}, "Options") == 1) {
        std::cout << "Options" << std::endl;
    };
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2+250, 300, 75}, "Exit") == 1) {
        CloseWindow();
    };
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    
    
};

void Menu::close() {
    
};