#pragma once
#include <iostream>

struct EnemyInfo {
	std::string moveTexture;
	std::string attackTexture;
	int left, top;
	int frameWidth, frameHeight;
	int moveFrames, attackFrames;
	float moveFrameTime, attackFrameTime;
};
