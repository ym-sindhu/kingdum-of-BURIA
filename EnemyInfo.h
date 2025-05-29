#pragma once
struct EnemyInfo {
	std::string moveTexture;
	std::string attackTexture;
	std::string deathTexture;
	int left, top;
	int frameWidth, frameHeight;
	int moveFrames, attackFrames, deathFrames;
	float moveFrameTime, attackFrameTime;
};
