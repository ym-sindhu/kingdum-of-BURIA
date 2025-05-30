#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Global.h"
#include "Player.h"
#include "Menu.h"
#include "LevelManager.h"
#include "MapLoader.h"
#include <json.hpp>
#include "Enemy.h"
#include "NormalEnemy.h"
#include "Boss.h"
#include "Obelisk.h"
#include "Sound.h"
using json = nlohmann::json;

class Game {
private:
	sf::RenderWindow window;
	SoundManager soundManager;
	GameState currentState;
	int level;
	bool levelFinished;
	Menu menu;
	LevelManager levelManager;
	Player player;
	MapLoader map;
	sf::View cameraView;
	std::vector<sf::FloatRect> groundRects;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::unique_ptr<Obelisk> obelisk;
	std::vector<sf::Sprite> tiles;
public:
	Game();
	void run();
	void handleEvents();
	void loadEnemies(int levelNumber);
	void loadBG(const int level);
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};