#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.h"
#include "Menu.h"
#include "LevelManager.h"
#include "UI.h"
#include "MapLoader.h"
#include <json.hpp>
#include "Enemy.h"
#include "NormalEnemy.h"
#include "Boss.h"
#include "EnemyInfo.h"
using json = nlohmann::json;

enum class GameState {
	MENU,PLAYING,PAUSED,GAME_OVER,LEVEL_COMPLETE
};
class Game {
private:
	sf::RenderWindow window;
	GameState currentState;
	int level;
	Menu menu;
	LevelManager levelManager;
	Player player;
	UI ui;
	MapLoader map;
	sf::View cameraView;
	std::vector<sf::FloatRect> groundRects;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	std::vector<std::unique_ptr<Enemy>> enemies;
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