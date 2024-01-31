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
    // Add one character of the dialogue to the displayed text.
    if (dialogueQueue.size() > 0) {
        if (this->displayedText.length() < this->dialogueQueue[0].text.length()) {
            this->displayedText += this->dialogueQueue[0].text[this->displayedText.length()];
        }
    }
    
    // Draw a rounded rectangle for the dialogue box near the bottom of the screen.
    DrawRectangleRounded(
        Rectangle{200, static_cast<float>(GetScreenHeight()) - 210, static_cast<float>(GetScreenWidth()) - 400, 200},
        0.1,
        0,
        this->border_color
    );
    
    DrawRectangleRounded(
        Rectangle{205, static_cast<float>(GetScreenHeight()) - 205, static_cast<float>(GetScreenWidth()) - 410, 190},
        0.1,
        0,
        this->fill_color
    );
    
    // Draw a rounded rectangle for the image to be displayed in.
    DrawRectangleRounded(
        Rectangle{210, static_cast<float>(GetScreenHeight()) - 200, 180, 180},
        0.1,
        0,
        this->border_color
    );
    
    // Draw the text
    if (dialogueQueue.size() > 0) {
        // Split text into lines that fit within the dialogue box.
        std::string text = this->displayedText;
        std::string line = "";
        std::vector<std::string> lines = std::vector<std::string>();
        
        int i = 0;
        while (i < text.length()) {
            if (text[i] == ' ') {
                if (MeasureText(line.c_str(), 20) > GetScreenWidth() - 720) {
                    lines.push_back(line);
                    line = "";
                }
                else {
                    line += text[i];
                    i++;
                }
            }
            else {
                line += text[i];
                i++;
            }
        }
        
        lines.push_back(line);
        
        // Reduce size of lines to 8
        while (lines.size() > 8) {
            lines.erase(lines.begin());
        }
        
        // Draw the lines.
        for (int i = 0; i < lines.size(); i++) {
            DrawText(
                lines[i].c_str(),
                400,
                GetScreenHeight() - 190 + 20 * i,
                20,
                this->text_color
            );
        }
    }
}