#include "dialogue.hpp"
#include <string>

DialogueBox::DialogueBox(Color border_color, Color fill_color, Color text_color) {
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->text_color = text_color;
    this->dialogueQueue = std::vector<Dialogue>();
}

void DialogueBox::clear() {
    this->dialogueQueue.clear();
}

void DialogueBox::push(std::string text, std::string name, Image image, Sound sound, bool skippable=true, bool autoSkip=false) {
    Dialogue dialogue;
    dialogue.name = name;
    dialogue.text = text;
    dialogue.sound = sound;
    dialogue.skippable = skippable;
    dialogue.autoSkip = autoSkip;
    
    // Resize the image to fit in the dialogue box.
    ImageResize(&image, 180, 180);
    dialogue.image = LoadTextureFromImage(image);
    
    this->dialogueQueue.insert(this->dialogueQueue.begin(), dialogue);
}

void DialogueBox::draw() {
    // If there is dialogue in the queue, display it.
    if (dialogueQueue.size() > 0) {
        dialogueScrollTimer++;
        
        if (this->displayedText.length() == 0) {
            // Play the sound
            PlaySound(this->dialogueQueue[0].sound);
            
            // Calcuate dialogue scroll speed based on sound duration.
            // Use doubles during calculation then cast to int.
            this->dialogueScrollSpeed = static_cast<int>(30.0 / (static_cast<double>(this->dialogueQueue[0].text.length()) / (static_cast<double>(this->dialogueQueue[0].sound.frameCount) / 48000.0)));
        }
        
        // Add characters to the displayed text at the speed of dialogueScrollSpeed. (Do this once per second.)
        if (this->displayedText.length() < this->dialogueQueue[0].text.length()) {
            if (dialogueScrollTimer % dialogueScrollSpeed == 0) {
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
        
        // Draw the name with bold text
        // TODO: Implement bold text
        DrawText(
            this->dialogueQueue[0].name.c_str(),
            400,
            GetScreenHeight() - 200,
            20,
            this->text_color
        );
        
        // Draw the image
        DrawTexture(this->dialogueQueue[0].image, 210, GetScreenHeight() - 200, WHITE);
        
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
            
            // Reduce size of lines to 7
            while (lines.size() > 7) {
                lines.erase(lines.begin());
            }
            
            // Draw the lines.
            for (int i = 0; i < lines.size(); i++) {
                DrawText(
                    lines[i].c_str(),
                    400,
                    GetScreenHeight() - 170 + 20 * i,
                    20,
                    this->text_color
                );
            }
        }
        
        // If the up arrow key or spacebar is pressed and the text is scrolling, skip to the end of the text. If the text is not scrolling, remove the current dialogue from the queue.
        if (IsKeyPressed(KEY_ENTER)) {
            if (this->displayedText.length() < this->dialogueQueue[0].text.length()) {
                this->displayedText = this->dialogueQueue[0].text;
            }
            else {
                StopSound(this->dialogueQueue[0].sound);
                this->dialogueQueue.erase(this->dialogueQueue.begin());
                this->displayedText = "";
            }
        }
    }
}