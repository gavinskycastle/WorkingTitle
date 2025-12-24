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

MenuState Menu::draw() {
    bool exit = false;
    // Draw a transparent rectangle to darken the background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 127});
    DrawTexture(this->logoTexture, GetScreenWidth()/2 - this->logoTexture.width/2, static_cast<float>(GetScreenHeight())/2-315, WHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(this->fillColor));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(this->textColor));
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(this->borderColor));
    GuiSetStyle(BUTTON, BORDER_WIDTH, 4);
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2-100, 300, 75}, "Grammar demo level") == 1) {
        this->selectedLevel = 1;
    };
    if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2, 300, 75}, "Chemistry demo level") == 1) {
        this->selectedLevel = 2;
    };
    // if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2+50, 300, 75}, "Play demo level 3") == 1) {
    //     this->selectedLevel = 3;
    // };
    // if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2+150, 300, 75}, "Options") == 1) {
    //     std::cout << "Options" << std::endl;
    // };
    #ifndef PLATFORM_WEB
        if (GuiButton(Rectangle {static_cast<float>(GetScreenWidth())/2-150, static_cast<float>(GetScreenHeight())/2+100, 300, 75}, "Exit") == 1) {
            exit = true;
        };
    #endif
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    
    // Draw version number in white at the bottom center of the screen
    DrawText("v0.2.1", GetScreenWidth()/2 - MeasureText("v0.2.1", 24)/2, GetScreenHeight()-30, 24, WHITE);
    
    return MenuState{this->selectedLevel, !exit};
};

MenuState Menu::drawExit() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(this->fillColor));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(this->textColor));
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(this->borderColor));
    GuiSetStyle(BUTTON, BORDER_WIDTH, 4);
    if (GuiButton(Rectangle {10.0f, 10.0f, 200, 50}, "Go to main menu") == 1) {
        this->selectedLevel = 0;
    };
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    
    return MenuState{this->selectedLevel, true};
};

void Menu::close() {
    
};