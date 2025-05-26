#include "LevelManager.h"

LevelManager::LevelManager() : currentLevel(1) {}

void LevelManager::loadLevel(int level) {
    currentLevel = level;
    // load level assets
}

void LevelManager::saveProgress() {
    std::ofstream file("data/Level.txt");
    if (file.is_open()) {
        file << currentLevel;
        file.close();
    }
}

void LevelManager::loadProgress() {
    std::ifstream file("data/Level.txt");
    if (file.is_open()) {
        file >> currentLevel;
        file.close();
    }
}

int LevelManager::getLevel() const {
    return currentLevel;
}