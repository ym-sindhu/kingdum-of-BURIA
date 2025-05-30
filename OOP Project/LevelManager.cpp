#include "LevelManager.h"
const std::string saveFile = "C:\\Users\\moeez\\source\\repos\\OOP Project\\OOP Project\\Data\\save.txt";
LevelManager::LevelManager() { currentLevel = 1; }
 
void LevelManager::loadSavedLevel() {
    std::ifstream file(saveFile);
    if (file.is_open()) {
        file >> currentLevel;
        file.close();
    }
    else {
        currentLevel = 1; 
    }
}

void LevelManager::saveLevel() const {
    std::ofstream file(saveFile);
    if (!file.is_open())
        std::cout << "Failed to open file" << "\n";
    if (file.is_open()) {
        file << currentLevel;
        file.close();
    }
}
void LevelManager::setLevel(int level) {
    currentLevel = level;
}
int LevelManager::getLevel() const {
    return currentLevel;
}
std::string LevelManager::getMapFilename() const {
    return "Assets/Maps/level" + std::to_string(currentLevel) + ".tmj";
}

std::string LevelManager::getMapTextureName() const {
    return "Assets/Textures/level" + std::to_string(currentLevel) + ".png";
}
void LevelManager::nextLevel() {
    currentLevel++;
    saveLevel();
}