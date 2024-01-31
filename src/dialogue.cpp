#include "dialogue.hpp"
#include <string>
#include <iostream>

DialogueBox::DialogueBox(Color border_color, Color fill_color, Color text_color) {
    std::cout << "DialogueBox constructor called." << std::endl;
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->text_color = text_color;
    this->dialogueQueue = std::vector<Dialogue>();
}

void DialogueBox::clear() {
    this->dialogueQueue.clear();
}

void DialogueBox::push(std::string text, Sound sound, double duration=0, bool skippable=true, bool autoSkip=false, bool newPage=true) {
    Dialogue dialogue;
    dialogue.text = text;
    dialogue.sound = sound;
    dialogue.duration = duration;
    dialogue.skippable = skippable;
    dialogue.autoSkip = autoSkip;
    dialogue.newPage = newPage;
    
    this->dialogueQueue.insert(this->dialogueQueue.begin(), dialogue);
}

void DialogueBox::draw() {
    // Draw a rounded rectangle for the dialogue box near the bottom of the screen.
    DrawRectangleRounded(
        Rectangle{0, static_cast<float>(GetScreenHeight()) - 200, static_cast<float>(GetScreenWidth()), 200},
        0.1,
        0,
        this->border_color
    );
    
    DrawRectangleRounded(
        Rectangle{5, static_cast<float>(GetScreenHeight()) - 195, static_cast<float>(GetScreenWidth()) - 10, 190},
        0.1,
        0,
        this->fill_color
    );
    
    // Draw a rounded rectangle for the image to be displayed in.
    DrawRectangleRounded(
        Rectangle{10, static_cast<float>(GetScreenHeight()) - 190, 180, 180},
        0.1,
        0,
        this->border_color
    );
    
    // Draw the text
    if (dialogueQueue.size() > 0) {
        DrawText(
            this->dialogueQueue[0].text.c_str(),
            200,
            GetScreenHeight() - 190,
            20,
            this->text_color
        );
    }
}