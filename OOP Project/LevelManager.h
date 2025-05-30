#pragma once
#include <string>
#include <iostream>
#include <fstream>

class LevelManager {
private:
    int currentLevel;
    const std::string saveFile;

public:
    LevelManager();

    void loadSavedLevel();

    void saveLevel() const;

    void setLevel(int level);

    int getLevel() const;

    std::string getMapFilename() const;

    std::string getMapTextureName() const;
    
    void nextLevel();
};
