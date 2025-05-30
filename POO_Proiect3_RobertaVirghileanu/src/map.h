#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MapLoadException.h"
#include "InvalidPlayerException.h"
#include "EmptyMapException.h"
#include <iostream>

const int MAX_ROWS = 50;
const int MAX_COLS = 50;

template<typename T>
class Map {
private:
    char mapData[MAX_ROWS][MAX_COLS];
    int width;
    int height;
    float tileSize;
    sf::Vector2i playerStart;

    sf::RectangleShape wallShape;
    sf::CircleShape dotShape;

    T extraInfo;  // atribut dependent de T

public:
    // constructor care să ”arunce” excepții
    Map(const char* filename, float tileSize);

    // getteri pentru informații despre hartă
    sf::Vector2i getPlayerStart() const;
    int getWidth() const;
    int getHeight() const;
    float getTileSize() const;

    // verificări și acțiuni asupra hărții
    bool isWall(int row, int col) const;
    bool isDot(int row, int col) const;
    void eatDot(int row, int col);

    // desenarea hărții
    void draw(sf::RenderWindow& window);

    // funcție dependentă de T
    T getExtraInfo() const { return extraInfo; }

    // setter pentru extraInfo
    void setExtraInfo(const T& info) { extraInfo = info; }

    // friend template function
    template<typename U>
    friend void printTileInfo(const Map<U>& map, int row, int col);
};

// funcție template liberă
template<typename U>
void printTileInfo(const Map<U>& map, int row, int col) {
    std::cout << "Tile at [" << row << "][" << col << "] = " << map.mapData[row][col]
              << " | ExtraInfo: " << map.extraInfo << std::endl;
}

// includ implementarea șablonului
#include "Map.tpp"
