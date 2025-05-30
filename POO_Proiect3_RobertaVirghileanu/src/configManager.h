#pragma once
//clasa singleton
class ConfigManager {
public:
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }

    float getTileSize() const { return tileSize; }
    void setTileSize(float size) { tileSize = size; }

private:
    ConfigManager() : tileSize(32.0f) {} // constructor privat cu valoare default
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    float tileSize;
};
