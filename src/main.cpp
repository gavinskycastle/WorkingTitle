#include "main.hpp"
#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"
#include "platform.hpp"
#include "dialogue.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>
#include "level.hpp"
#include "menu.hpp"
#include "pickup.hpp"

Color borderColor;
Color backgroundColor;
Color fillColor;
Color fillLight;
Color textColor;

Color borderColorAlt;
Color fillColorAlt;

std::vector<Level*> levels;
Level* currentLevel;

Menu* mainMenu;
MenuState menuState = MenuState{0, true};

Platform* ground;
std::vector<std::string> englishTextToRender;

int selectedLevel = 0;

Level* level1Factory() {
    return new Level(Vector2{100, 450}, // Level 1: English based level
            std::vector<Platform*>{ground, new Platform(300, 340, 169, 50, borderColorAlt, fillColorAlt, 0, 5, false),
            new Platform(527, 340, 80, 50, borderColorAlt, fillColorAlt, 0, 5, false),
            new Platform(665, 340, 58, 50, borderColorAlt, fillColorAlt, 0, 5, false),
            new Platform(781, 340, 402, 50, borderColorAlt, fillColorAlt, 0, 5, false),
            new Platform(1241, 340, 106, 50, borderColorAlt, fillColorAlt, 0, 5, false),
            new Platform(1405, 340, 123, 50, borderColorAlt, fillColorAlt, 0, 5, false),
            new Platform(1586, 340, 147, 50, borderColorAlt, fillColorAlt, 0, 5, false)},
            std::vector<Pickup*>{new Pickup(300+169-6, 330, "", false, false),
            new Pickup(527+80-6, 330, "", false, false),
            new Pickup(665+58-6, 330, "", false, false),
            new Pickup(781+402-6, 330, "", false, false),
            new Pickup(1241+106-6, 330, "", false, false),
            new Pickup(1405+123-6, 330, "", false, false),
            new Pickup(1586+147-6, 330, "", false, false),
            
            new Pickup(600, 500, ",", false, true),
            new Pickup(700, 500, "-", false, true),
            new Pickup(800, 500, ",", false, true),
            new Pickup(900, 500, "-", false, true),
            new Pickup(1000, 500, ":", false, true),
            new Pickup(1100, 500, ".", false, true),
            new Pickup(1200, 500, " ", false, true)},
            std::vector<std::string>{"The Narrator", "The Narrator"},
            std::vector<std::string>{
                "This level will test your knowledge of basic English grammar. Place the punctuation marks in the correct slots to complete the sentences. Good luck!",
                "Welcome to Working Title! Working Title is a game about developing your knowledge of various school subjects through the fun of puzzle platforming. Press WASD to move and jump, shift to sprint, E to pick up and place each of the objects in the slots, and space to skip this dialogue."
                },
            std::vector<Image>{LoadImage("assets/narrator.png"), LoadImage("assets/narrator.png")},
            std::vector<Sound>{LoadSound("assets/testSound.ogg"), LoadSound("assets/testSound.ogg")},
            borderColor, fillColor, textColor);
}

Level* level2Factory() {
    return new Level(Vector2{100, 400}, // Level 2: Chemistry based level
        std::vector<Platform*>{ground},
        std::vector<Pickup*>{},
        std::vector<std::string>{},
        std::vector<std::string>{},
        std::vector<Image>{},
        std::vector<Sound>{},
        borderColor, fillColor, textColor);
}

Level* level3Factory() {
    return new Level(Vector2{100, 400}, // Level 3: Algebra based level
        std::vector<Platform*>{ground},
        std::vector<Pickup*>{},
        std::vector<std::string>{},
        std::vector<std::string>{},
        std::vector<Image>{},
        std::vector<Sound>{},
        borderColor, fillColor, textColor);
}

void init_app() {
    InitAudioDevice();
    SetTargetFPS(60);
    
    borderColor = Color{11, 36, 71, 255};
    backgroundColor = Color{25, 55, 109, 255};
    fillColor = Color{87, 108, 188, 255};
    fillLight = Color{165, 215, 232, 255};
    textColor = Color{0, 0, 0, 255};
    
    borderColorAlt = Color{71, 35, 11, 255};
    fillColorAlt = Color{187, 124, 86, 255};
    
    ground = new Platform(0, 585, 1920, 540, borderColor, fillColor, 0, 5, true);
    
    englishTextToRender = std::vector<std::string>{"The sixteen", "year", "old", "student introduced his friends", "Natalie", "Jackson", "and Ethan"};
    
    levels = std::vector<Level*>{
        nullptr, // Level 0
       
        level1Factory(), // Level 1: English based level
        
        level2Factory(), // Level 2: Chemistry based level
        
        level3Factory() // Level 3: Algebra based level
    };
    
    mainMenu = new Menu(borderColor, fillColor, textColor);
}

bool app_loop() {
    BeginDrawing();
        ClearBackground(backgroundColor);
        
        if (selectedLevel == 0) {
            menuState = mainMenu->draw();
            if (menuState.selectedLevel != selectedLevel) {
                selectedLevel = menuState.selectedLevel;
                switch (selectedLevel) {
                    case 1:
                        levels[selectedLevel] = level1Factory();
                        break;
                    case 2:
                        levels[selectedLevel] = level2Factory();
                        break;
                    case 3:
                        levels[selectedLevel] = level3Factory();
                        break;
                }
                currentLevel = levels[selectedLevel];
            }
        } else {
            currentLevel->draw();
            menuState = mainMenu->drawExit();
            if (menuState.selectedLevel != selectedLevel) {
                selectedLevel = menuState.selectedLevel;
                currentLevel = levels[selectedLevel];
            }
        }
        
        if (selectedLevel == 1) {
            // Draw each piece of text in the englishTextToRender vector with a 70 pixel gap between each, using the size of the previous text to determine the x position of the next text.
            int x = 312;
            for (int i = 0; i < englishTextToRender.size(); i++) {
                DrawText(englishTextToRender[i].c_str(), x, 352, 25, BLACK);
                int textWidth = MeasureText(englishTextToRender[i].c_str(), 25);
                //std::cout << "Rectangle for the text '" << englishTextToRender[i].c_str() << "': " << "x: " << x-12 << ", y: " << 340 << ", width: " << textWidth+24 << ", height: " << 50 << std::endl;
                x += textWidth + 82;
            }
        }
        
    EndDrawing();
    
    return menuState.exit;
}

void deinit_app() {
}