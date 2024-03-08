#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "../libs/raylib/src/raylib.h"

struct Dialogue {
    Texture2D image;
    std::string name;
    std::string text;
    Sound sound;
    
    bool skippable;
    bool autoSkip;
};

class DialogueBox {
    public:
        DialogueBox(Color border_color, Color fill_color, Color text_color);
        
        // Clears the dialogue queue.
        void clear();
        
        // Pushes a new dialogue onto the queue.
        void push(std::string text, std::string name, Image image, Sound sound, bool skippable, bool autoSkip);
        
        // Draws and updates the dialogue box onscreen. Should be called every frame.
        void draw();
    
    private:
        int x;
        int y;
        Color border_color;
        Color fill_color;
        Color text_color;
        
        std::string displayedText;
        
        int dialogueScrollSpeed;
        int dialogueScrollTimer;
        std::vector<Dialogue> dialogueQueue;
};

#endif // DIALOGUE_HPP