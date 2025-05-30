#pragma once
#include "Ghost.h"
#include <SFML/Graphics.hpp>

class ChaseGhost : public Ghost {
public:
    ChaseGhost(float startX, float startY, float tileSize);

    void update(const sf::Vector2i& playerPos) override;
    void draw(sf::RenderWindow& window) override;

    ChaseGhost(const ChaseGhost&) = default;
    Ghost* clone() const override;

private:
    sf::Texture texture;
    sf::Sprite sprite;

    void updateSpritePosition();
};
