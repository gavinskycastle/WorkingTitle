#include "level.hpp"

Level::Level(Vector2 startPosition, std::vector<Platform*> platforms,
    std::vector<std::string> dialogueNames,
    std::vector<std::string> dialogueTexts,
    std::vector<Image> dialogueImages,
    std::vector<Sound> dialogueSounds,
    Color border_color, Color fill_color, Color text_color)
{
    this->player = new Player(startPosition.x, startPosition.y, border_color, fill_color);
    this->platforms = platforms;
    this->dialogueBox = new DialogueBox(border_color, fill_color, text_color);
    for (int i = 0; i < dialogueNames.size(); i++) {
        this->dialogueBox->push(dialogueTexts[i], dialogueNames[i], dialogueImages[i], dialogueSounds[i], true, false);
    }
}

void Level::draw() {
    this->player->draw();
    for (int i = 0; i < this->platforms.size(); i++) {
        this->platforms[i]->draw();
    }
    this->dialogueBox->draw();
}

void Level::close() {
    this->player->close();
    delete this->player;
    delete this->dialogueBox;
    for (int i = 0; i < this->platforms.size(); i++) {
        delete this->platforms[i];
    }
}