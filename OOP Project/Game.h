#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Menu.h"
#include "LevelManager.h"
#include "UI.h"
#include "MapLoader.h"
#include <json.hpp>
using json = nlohmann::json;

enum class GameState {
	MENU,PLAYING,PAUSED,GAME_OVER,LEVEL_COMPLETE
};

class Game {
private:
	sf::RenderWindow window;
	GameState currentState;
	Menu menu;
	LevelManager currentLevel;
	Player player;
	UI ui;
	MapLoader map;
	sf::View cameraView;
	std::vector<sf::FloatRect> groundRects;

	std::vector<sf::Sprite> tiles;
public:
	Game();
	void run();
	void handleEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};