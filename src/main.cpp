#include "main.hpp"
#include "../libs/raylib/src/raylib.h"
#include "../libs/raygui/src/raygui.h"
#include "helper.hpp"
#include "platform.hpp"

Color borderColor;
Color backgroundColor;
Color fillColor;
Color fillLight;

Platform testPlatform = Platform(100, 100, 100, 100, borderColor, fillColor, 0, 5);

void init_app() {
    borderColor = Color{11, 36, 71};
    backgroundColor = Color{25, 55, 109};
    fillColor = Color{87, 108, 188};
    fillLight = Color{165, 215, 232};
}

bool app_loop() {
    BeginDrawing();
    ClearBackground(backgroundColor);
    
    //testPlatform.draw();
    
    EndDrawing();

    return true;
}

void deinit_app() {
}