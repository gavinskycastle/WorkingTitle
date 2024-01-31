#include "main.hpp"
#include "../libs/raylib/src/raylib.h"
#include "../libs/raygui/src/raygui.h"
#include "helper.hpp"
#include "platform.hpp"
#include "dialogue.hpp"
#include <iostream>

Color borderColor;
Color backgroundColor;
Color fillColor;
Color fillLight;

//Platform testPlatform = Platform(100, 100, 100, 100, borderColor, fillColor, 0, 5);
DialogueBox* testDialogueBox;

void init_app() {
    borderColor = Color{11, 36, 71, 255};
    backgroundColor = Color{25, 55, 109, 255};
    fillColor = Color{87, 108, 188, 255};
    fillLight = Color{165, 215, 232, 255};
    
    testDialogueBox = new DialogueBox(borderColor, fillColor, fillLight);
}

bool app_loop() {
    BeginDrawing();
    ClearBackground(backgroundColor);
    
    //testPlatform.draw();
    testDialogueBox->draw();
    
    //DrawRectangle(0, 0, 100, 100, borderColor);
    
    EndDrawing();

    return true;
}

void deinit_app() {
}