#include <iostream>
#include "Map.h" 
#include "Player.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "ChaseGhost.h"
#include "PatrolGhost.h"
#include "utile.h"
#include "MapLoadException.h"
#include "InvalidPlayerException.h"
#include "EmptyMapException.h"
#include "GhostFactory.h"
#include "configManager.h"

int main() {
    try {
        // Inițializez config și setez tileSize global
        auto& config = ConfigManager::getInstance();
        config.setTileSize(32.0f);
        float tileSize = config.getTileSize();

        // Încarc harta
        Map<char> gameMap("map.txt", tileSize); 
        gameMap.setExtraInfo('M'); // testare atribut T

        // Inițializez jucătorul
        sf::Vector2i startPos = gameMap.getPlayerStart();
        Player pacman(startPos.x, startPos.y, tileSize);

        // Inițializez fantomele folosind Factory Pattern
        Ghost* ghosts[1000];
        int ghostCount = 0;
        ghosts[ghostCount++] = GhostFactory::createGhost(GhostType::Random, 5, 5, tileSize);
        ghosts[ghostCount++] = GhostFactory::createGhost(GhostType::Chase, 7, 7, tileSize);
        ghosts[ghostCount++] = GhostFactory::createGhost(GhostType::Patrol, 10, 10, tileSize);

        // Inițializare fereastră
        int windowWidth = gameMap.getWidth() * tileSize;
        int windowHeight = gameMap.getHeight() * tileSize;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pac-Man");
        window.setFramerateLimit(60);

        sf::Clock ghostClock;
        float ghostMoveInterval = 0.6f;
        bool isGameOver = false;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (!isGameOver) {
                pacman.handleInput(gameMap);
                pacman.update(gameMap);

                if (gameMap.isDot(pacman.getRow(), pacman.getCol())) {
                    gameMap.eatDot(pacman.getRow(), pacman.getCol());
                }

                if (ghostClock.getElapsedTime().asSeconds() > ghostMoveInterval) {
                    updateGhosts(ghosts, ghostCount, pacman.getPosition());
                    ghostClock.restart();
                }

                for (int i = 0; i < ghostCount; i++) {
                    sf::Vector2i ghostPos = ghosts[i]->getPosition();
                    if (ghostPos == pacman.getPosition()) {
                        if (auto* chase = dynamic_cast<ChaseGhost*>(ghosts[i])) {
                            isGameOver = true;
                            break;
                        } else if (auto* random = dynamic_cast<RandomGhost*>(ghosts[i])) {
                            ghostMoveInterval = 1.2f;
                        } else if (auto* patrol = dynamic_cast<PatrolGhost*>(ghosts[i])) {
                            pacman = Player(startPos.x, startPos.y, tileSize);
                        }
                    }
                }

                window.clear(sf::Color::Black);
                gameMap.draw(window);
                pacman.draw(window);
                drawGhosts(ghosts, ghostCount, window);
                window.display();
            } else {
                window.clear(sf::Color::Red);
                window.display();
                sf::sleep(sf::seconds(3));
                window.close();
            }
        }

        // Eliberare memorie
        for (int i = 0; i < ghostCount; i++) {
            delete ghosts[i];
        }

        return 0;

    } catch (const MapLoadException& ex) {
        std::cerr << "Eroare la încărcarea hărții: " << ex.what() << std::endl;
        return 1;
    } catch (const InvalidPlayerPositionException& ex) {
        std::cerr << "Eroare: " << ex.what() << std::endl;
        return 3;
    } catch (const EmptyMapFileException& ex) {
        std::cerr << "Eroare fișier hartă gol: " << ex.what() << std::endl;
        return 4;
    } catch (const std::exception& ex) {
        std::cerr << "Eroare neașteptată: " << ex.what() << std::endl;
        return 2;
    }
}
