#pragma once
#include "Ghost.h"
#include "RandomGhost.h"
#include "ChaseGhost.h"
#include "PatrolGhost.h"

enum class GhostType { Random, Chase, Patrol };

class GhostFactory {
public:
    static Ghost* createGhost(GhostType type, int row, int col, float tileSize) {
        switch (type) {
            case GhostType::Random:
                return new RandomGhost(row, col, tileSize);
            case GhostType::Chase:
                return new ChaseGhost(row, col, tileSize);
            case GhostType::Patrol:
                return new PatrolGhost(row, col, tileSize, 15, false);
            default:
                return nullptr;
        }
    }
};
