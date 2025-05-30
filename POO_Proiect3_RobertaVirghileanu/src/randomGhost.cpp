#include "RandomGhost.h"
#include <iostream> // pentru std::cerr

RandomGhost::RandomGhost(float startX, float startY, float tileSize)
    : Ghost(startX, startY, tileSize, sf::Color::Red) {

    if (!texture.loadFromFile("randomGhost.png")) {
        std::cerr << "Eroare la incarcare randomGhost.png\n";
    }

    sprite.setTexture(texture);

    float scaleX = tileSize / texture.getSize().x;
    float scaleY = tileSize / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);

    updateSpritePosition();
}

void RandomGhost::update(const sf::Vector2i& playerPos) {
    int moveDirection = rand() % 4;
    if (moveDirection == 0 && row > 0) {
        row--;
    } else if (moveDirection == 1 && row < 10) {
        row++;
    } else if (moveDirection == 2 && col > 0) {
        col--;
    } else if (moveDirection == 3 && col < 10) {
        col++;
    }

    updateSpritePosition();
}

void RandomGhost::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

Ghost* RandomGhost::clone() const {
    return new RandomGhost(*this);
}

void RandomGhost::updateSpritePosition() {
    sprite.setPosition(col * tileSize, row * tileSize);
}
