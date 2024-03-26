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

Sound testSound;
Image testImage;

Platform* testPlatform;

Platform* ground;

Pickup* testPickup;
Pickup* testPickup2;

std::vector<Level*> levels;
Level* currentLevel;

Menu* testMenu;
MenuState menuState = MenuState{0, true};

int selectedLevel = 0;

void init_app() {
    InitAudioDevice();
    SetTargetFPS(60);
    
    testSound = LoadSound("assets/testSound.ogg");
    testImage = LoadImage("assets/testImage.png");
    
    borderColor = Color{11, 36, 71, 255};
    backgroundColor = Color{25, 55, 109, 255};
    fillColor = Color{87, 108, 188, 255};
    fillLight = Color{165, 215, 232, 255};
    textColor = Color{0, 0, 0, 255};
    
    testPlatform = new Platform(100, 100, 100, 100, borderColor, fillColor, 0, 5, false);
    ground = new Platform(10, 10, 600, 250, borderColor, fillColor, 0, 5, true);
    
    testPickup = new Pickup(300, 400, "H", false, true);
    testPickup2 = new Pickup(400, 400, "", false, false);
    
    levels = std::vector<Level*>{
        nullptr, // Level 0
        
        new Level(Vector2{100, 100}, // Level 1
            std::vector<Platform*>{testPlatform, ground},
            std::vector<Pickup*>{testPickup, testPickup2},
            std::vector<std::string>{"The Narrator"},
            std::vector<std::string>{"The FitnessGram Pacer test is a multistage aerobic capacity test that progressively gets more difficult as it continues. The 20 meter Pacer test will begin in 30 seconds. Line up at the start. The running speed starts slowly, but gets faster each minute after you hear this signal *boop*. A single lap should be completed each time you hear this sound *ding*. Remember to run in a straight line, and run as long as possible. The second time you fail to complete a lap before the sound, your test is over. The test will begin on the word start."},
            std::vector<Image>{testImage},
            std::vector<Sound>{testSound},
            borderColor, fillColor, textColor),
        
        new Level(Vector2{100, 100}, // Level 2
            std::vector<Platform*>{testPlatform, ground},
            std::vector<Pickup*>{},
            std::vector<std::string>{},
            std::vector<std::string>{},
            std::vector<Image>{},
            std::vector<Sound>{},
            borderColor, fillColor, textColor),
        
        new Level(Vector2{100, 100}, // Level 3
            std::vector<Platform*>{testPlatform, ground},
            std::vector<Pickup*>{},
            std::vector<std::string>{},
            std::vector<std::string>{},
            std::vector<Image>{},
            std::vector<Sound>{},
            borderColor, fillColor, textColor)
    };
    
    testMenu = new Menu(borderColor, fillColor, textColor);
}

bool app_loop() {
    BeginDrawing();
        ClearBackground(backgroundColor);
        
        if (selectedLevel == 0) {
            menuState = testMenu->draw();
            if (menuState.selectedLevel != selectedLevel) {
                selectedLevel = menuState.selectedLevel;
                currentLevel = levels[selectedLevel];
            }
        } else {
            currentLevel->draw();
        }
        
    EndDrawing();
    
    return menuState.exit;
}

void deinit_app() {
}