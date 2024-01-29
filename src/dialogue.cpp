#include "dialogue.hpp"

DialogueBox::DialogueBox(Color border_color, Color fill_color, Color text_color) {
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->text_color = text_color;
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
    
}