#pragma once
#include "Ghost.h"
#include <cstdlib> // pentru rand()
#include <SFML/Graphics.hpp>

class RandomGhost : public Ghost {
public:
    RandomGhost(float startX, float startY, float tileSize);

    void update(const sf::Vector2i& playerPos) override;
    void draw(sf::RenderWindow& window) override;

    RandomGhost(const RandomGhost&) = default;
    Ghost* clone() const override;

private:
    sf::Texture texture;
    sf::Sprite sprite;

    void updateSpritePosition();
};
