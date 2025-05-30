#include "PatrolGhost.h"
#include <iostream>

PatrolGhost::PatrolGhost(int startX, int startY, float tileSize, int range, bool vertical)
    : Ghost(startX, startY, tileSize, sf::Color::Blue),
      patrolRange(range),
      isVertical(vertical),
      direction(1) {

    if (!texture.loadFromFile("patrolGhost.png")) {
        std::cerr << "Eroare la incarcare patrolGhost.png\n";
    }
    sprite.setTexture(texture);

    float scaleX = tileSize / texture.getSize().x;
    float scaleY = tileSize / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);

    updateSpritePosition();
}

void PatrolGhost::update(const sf::Vector2i& playerPos) {
    if (isVertical) {
        if (direction == 1) {
            if (row < patrolRange) {
                row++;
            } else {
                direction = -1;
                row--;
            }
        } else {
            if (row > 0) {
                row--;
            } else {
                direction = 1;
                row++;
            }
        }
    } else {
        if (direction == 1) {
            if (col < patrolRange) {
                col++;
            } else {
                direction = -1;
                col--;
            }
        } else {
            if (col > 0) {
                col--;
            } else {
                direction = 1;
                col++;
            }
        }
    }

    updateSpritePosition();
}

void PatrolGhost::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

Ghost* PatrolGhost::clone() const {
    return new PatrolGhost(*this);
}

void PatrolGhost::updateSpritePosition() {
    sprite.setPosition(col * tileSize, row * tileSize);
}
