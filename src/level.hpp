#include "player.hpp"
#include "dialogue.hpp"
#include "pickup.hpp"

#ifndef LEVEL_H
#define LEVEL_H

class Level {
    public:
        Level(Vector2 startPosition, std::vector<Platform*> platforms,
    std::vector<Pickup*> pickups,
    std::vector<std::string> dialogueNames,
    std::vector<std::string> dialogueTexts,
    std::vector<Image> dialogueImages,
    std::vector<Sound> dialogueSounds,
    Color border_color, Color fill_color, Color text_color);
        void draw();
        void close();
    
        Player* player;
        std::vector<Platform*> platforms;
        std::vector<Pickup*> pickups;
        DialogueBox* dialogueBox;
};

#endif // LEVEL_H