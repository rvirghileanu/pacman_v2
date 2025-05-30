#pragma once

#include "Ghost.h"
#include <SFML/Graphics.hpp>

class PatrolGhost : public Ghost {
public:
    PatrolGhost(int startX, int startY, float tileSize, int range, bool vertical);

    void update(const sf::Vector2i& playerPos) override;
    void draw(sf::RenderWindow& window) override;

    Ghost* clone() const override;

private:
    int patrolRange;
    bool isVertical;
    int direction;

    sf::Texture texture;
    sf::Sprite sprite;

    void updateSpritePosition();
};
