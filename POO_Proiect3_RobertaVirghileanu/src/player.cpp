#include "Player.h"
#include <iostream> // pentru std::cerr

Player::Player(int startX, int startY, float tileSize)
    : row(startY), col(startX), tileSize(tileSize), moving(false), directionX(0), directionY(0) {

    if (!texture.loadFromFile("pacman.png")) {
        std::cerr << "Eroare la incarcare pacman.png\n";
    }
    sprite.setTexture(texture);

    // redimensionare sprite dacă e nevoie să se potrivească tileSize
    float scaleX = tileSize / texture.getSize().x;
    float scaleY = tileSize / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);

    updateSpritePosition();
}

void Player::handleInput(const Map<char>& map) {
    if (!moving) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && row > 0) {
            directionX = 0;
            directionY = -1;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && row < map.getHeight() - 1) {
            directionX = 0;
            directionY = 1;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && col > 0) {
            directionX = -1;
            directionY = 0;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && col < map.getWidth() - 1) {
            directionX = 1;
            directionY = 0;
            moving = true;
        }
    }
}

void Player::update(Map<char>& map) {
    if (moving) {
        if (moveClock.getElapsedTime().asSeconds() > 0.2f) {
            moveClock.restart();

            if (!map.isWall(row + directionY, col + directionX)) {
                row += directionY;
                col += directionX;
            }

            updateSpritePosition();
            moving = false;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Player::getRow() const {
    return row;
}

int Player::getCol() const {
    return col;
}

sf::Vector2i Player::getPosition() const {
    return sf::Vector2i(col, row);
}

void Player::updateSpritePosition() {
    sprite.setPosition(col * tileSize, row * tileSize);
}
