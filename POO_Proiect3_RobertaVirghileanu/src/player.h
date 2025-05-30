#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Player {
public:
    Player(int startX, int startY, float tileSize);

    void handleInput(const Map<char>& map);
    void update(Map<char>& map);
    void draw(sf::RenderWindow& window);

    int getRow() const;
    int getCol() const;

    sf::Vector2i getPosition() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;

    int row, col;
    float tileSize;

    int directionX, directionY;
    bool moving;
    sf::Clock moveClock;

    void updateSpritePosition();
};
