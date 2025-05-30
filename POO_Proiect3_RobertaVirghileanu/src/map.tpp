#pragma once

#include <fstream>
#include <iostream>
#include <cstring>
#include "Map.h"

template<typename T>
Map<T>::Map(const char* filename, float tileSize) : tileSize(tileSize), width(0), height(0), extraInfo() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw MapLoadException("Nu pot deschide fișierul: " + std::string(filename));
    }

    char line[MAX_COLS + 1];
    bool foundSomething = false;
    bool foundPlayer = false;

    while (file.getline(line, MAX_COLS)) {
        int len = std::strlen(line);
        if (len > width) width = len;

        for (int col = 0; col < len; ++col) {
            char c = line[col];
            if (c == 'P') {
                if (foundPlayer) {
                    throw InvalidPlayerPositionException("Poziția jucătorului (P) apare de mai multe ori în fișierul hărții!");
                }
                playerStart = sf::Vector2i(col, height);
                mapData[height][col] = '.';
                foundPlayer = true;
            } else {
                mapData[height][col] = c;
            }
        }

        height++;
        if (height >= MAX_ROWS) break;
        foundSomething = true;
    }

    if (!foundSomething || height == 0) {
        throw EmptyMapFileException("Fișierul este gol sau nu conține o hartă validă.");
    }

    if (!foundPlayer) {
        throw InvalidPlayerPositionException("Poziția jucătorului (P) nu a fost găsită în fișierul hărții!");
    }

    wallShape.setSize(sf::Vector2f(tileSize, tileSize));
    wallShape.setFillColor(sf::Color::Blue);

    dotShape.setRadius(tileSize / 6);
    dotShape.setFillColor(sf::Color::White);
    dotShape.setOrigin(dotShape.getRadius(), dotShape.getRadius());
}

template<typename T>
sf::Vector2i Map<T>::getPlayerStart() const {
    return playerStart;
}

template<typename T>
int Map<T>::getWidth() const {
    return width;
}

template<typename T>
int Map<T>::getHeight() const {
    return height;
}

template<typename T>
float Map<T>::getTileSize() const {
    return tileSize;
}

template<typename T>
bool Map<T>::isWall(int row, int col) const {
    return mapData[row][col] == '#';
}

template<typename T>
bool Map<T>::isDot(int row, int col) const {
    return mapData[row][col] == '.';
}

template<typename T>
void Map<T>::eatDot(int row, int col) {
    mapData[row][col] = ' ';
}

template<typename T>
void Map<T>::draw(sf::RenderWindow& window) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (isWall(row, col)) {
                wallShape.setPosition(col * tileSize, row * tileSize);
                window.draw(wallShape);
            } else if (isDot(row, col)) {
                dotShape.setPosition(col * tileSize + tileSize / 2, row * tileSize + tileSize / 2);
                window.draw(dotShape);
            }
        }
    }
}
