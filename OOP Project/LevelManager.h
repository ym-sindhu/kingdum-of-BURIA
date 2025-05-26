#pragma once
#include <fstream>

class LevelManager {
private:
    int currentLevel;

public:
    LevelManager();
    void loadLevel(int level);
    void saveProgress();
    void loadProgress();
    int getLevel() const;
};