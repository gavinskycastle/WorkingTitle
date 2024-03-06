#include "main.hpp"
#include "../libs/raylib/src/raylib.h"
#include "../libs/raygui/src/raygui.h"
#include "helper.hpp"
#include "platform.hpp"
#include "dialogue.hpp"
#include "player.hpp"
#include <iostream>

Color borderColor;
Color backgroundColor;
Color fillColor;
Color fillLight;
Color textColor;

//Platform testPlatform = Platform(100, 100, 100, 100, borderColor, fillColor, 0, 5);
DialogueBox* testDialogueBox;

Sound testSound;
Image testImage;

Platform* testPlatform;

Platform* ground;

Player* testPlayer;

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
    
    testDialogueBox = new DialogueBox(borderColor, fillColor, textColor);
    testPlatform = new Platform(100, 100, 100, 100, borderColor, fillColor, 0, 5, false);
    
    ground = new Platform(10, 10, 600, 250, borderColor, fillColor, 0, 5, true);
    
    testDialogueBox->push("The FitnessGram Pacer test is a multistage aerobic capacity test that progressively gets more difficult as it continues. The 20 meter Pacer test will begin in 30 seconds. Line up at the start. The running speed starts slowly, but gets faster each minute after you hear this signal *boop*. A single lap should be completed each time you hear this sound *ding*. Remember to run in a straight line, and run as long as possible. The second time you fail to complete a lap before the sound, your test is over. The test will begin on the word start. On your mark, get ready, start.", "The Narrator", 
     testImage, testSound, true, false);
     
    testPlayer = new Player(100, 100, borderColor, fillColor);
}

bool app_loop() {
    BeginDrawing();
    ClearBackground(backgroundColor);
    
    testDialogueBox->draw();
    testPlatform->draw();
    
    ground->draw();
    
    ground->move(0, 2);
    
    testPlayer->draw();
    
    EndDrawing();

    return true;
}

void deinit_app() {
    testPlayer->close();
}