#include "chaseGhost.h"
#include <iostream> // pentru std::cerr

ChaseGhost::ChaseGhost(float startX, float startY, float tileSize)
    : Ghost(startX, startY, tileSize, sf::Color::Green) {

    if (!texture.loadFromFile("chaseGhost.png")) {
        std::cerr << "Eroare la incarcare chaseGhost.png\n";
    }

    sprite.setTexture(texture);

    // Scalare pentru potrivire cu tileSize
    float scaleX = tileSize / texture.getSize().x;
    float scaleY = tileSize / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);

    updateSpritePosition();
}

void ChaseGhost::update(const sf::Vector2i& playerPos) {
    if (playerPos.x > col) {
        col++;
    } else if (playerPos.x < col) {
        col--;
    }

    if (playerPos.y > row) {
        row++;
    } else if (playerPos.y < row) {
        row--;
    }

    updateSpritePosition();
}

void ChaseGhost::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

Ghost* ChaseGhost::clone() const {
    return new ChaseGhost(*this);
}

void ChaseGhost::updateSpritePosition() {
    sprite.setPosition(col * tileSize, row * tileSize);
}
