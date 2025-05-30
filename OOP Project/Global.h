#pragma once
#include <iostream>

struct EnemyInfo {
	std::string moveTexture;
	std::string attackTexture;
	std::string deathTexture;
	int left, top;
	int frameWidth, frameHeight;
	int moveFrames, attackFrames, deathFrames;
	float moveFrameTime, attackFrameTime, deathFrameTime;
};

enum class EntityType {
    PLAYER,
    ENEMY,
    BOSS
};

enum class GameState {
    MENU, PLAYING, PAUSED, GAME_OVER, LEVEL_COMPLETE,FINISH
};