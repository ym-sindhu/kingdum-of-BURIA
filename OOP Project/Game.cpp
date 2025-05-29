#include "Game.h"	
EnemyInfo level1Enemy = {
	"Assets/Enemies/Enemy_walk1.png",
	"Assets/Enemies/Enemy_attack1.png",
	42, 61, 128, 65,
	10, 4,
	0.2f, 0.1f
};
EnemyInfo level1Boss = {
	"Assets/Boss/boss_walk1.png",
	"Assets/Boss/boss_attack1.png",
	80, 44 ,250,124,
	8, 8,
	0.2f ,0.2f
};

Game::Game() : window(sf::VideoMode(800, 600), "Kingdum of Buria"), currentState(GameState::MENU)
{
	levelManager.loadSavedLevel();
	map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
	loadBG(levelManager.getLevel());
	if (!font.loadFromFile("Assets/Fonts/HoldMoney-Regular.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
	}
}

void Game::run() {
	sf::Clock clock;
	cameraView.setSize(800, 600); // same as window
	cameraView.setCenter(player.getPosition());

	map.load();

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		handleEvents();
		update(deltaTime);		
		render(window);
	}
}

void Game::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) 
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (currentState == GameState::MENU && event.type == sf::Event::KeyPressed) 
			if (event.key.code == sf::Keyboard::Enter) 
			{	
				levelManager.setLevel(1); // New Game
				levelManager.saveLevel();
				level = levelManager.getLevel();
				map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
				map.load();
				loadEnemies(1);
				std::cout << "Current Level : " << levelManager.getLevel() << "\n";
				currentState = GameState::PLAYING;
			}
			else if (event.key.code == sf::Keyboard::C) {
				levelManager.loadSavedLevel(); // Continue
				map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
				map.load();
				player.reset();
				currentState = GameState::PLAYING;
			}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
		{
			if (currentState == GameState::PLAYING)
				currentState = GameState::PAUSED;
			else if (currentState == GameState::PAUSED)
				currentState = GameState::PLAYING;
		}
		if (currentState == GameState::LEVEL_COMPLETE && event.key.code == sf::Keyboard::Enter) {
			levelManager.nextLevel(); 
			map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
			player.reset();
			currentState = GameState::PLAYING;
		}
		if (currentState == GameState::GAME_OVER && event.key.code == sf::Keyboard::Enter) {
			//levelManager.resetToFirstLevel();
			map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
			player.reset();
			currentState = GameState::PLAYING;
		}
	}
}

void Game::loadEnemies(int levelNumber)
{
	enemies.clear();
	std::cout << "Spawning enemies for level: " << 1 << std::endl;

	if (level == 1) {
		std::cout << "Pushing back enemies for level : " << levelManager.getLevel() << "\n";
		enemies.push_back(std::make_unique<NormalEnemy>(
			level1Enemy ,// texture path
			sf::Vector2f(500, 312),           // position
			15.f,                             // speed
			100.f,                            // patrol range
			true                              
		));
		enemies.push_back(std::make_unique<NormalEnemy>(
			level1Enemy,                      
			sf::Vector2f(800, 312),           
			15.f,                             
			100.f,                            
			true                              
		));
		std::cout << "Enemy size : " << enemies.size();
		enemies.push_back(std::make_unique<Boss>(
			level1Boss,
			sf::Vector2f(1400, 200),
			1000,  
			40.f
		));
	}
}

void Game::loadBG(const int level)
{
	std::string bgPath = "Assets/BG/level" + std::to_string(level) + "_BG.png";
	if (!backgroundTexture.loadFromFile(bgPath)) {
		std::cerr << "Failed to load background: " << bgPath << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		window.getSize().x / backgroundSprite.getLocalBounds().width,
		window.getSize().y / backgroundSprite.getLocalBounds().height );

	window.draw(backgroundSprite);
}

void Game::update(float deltaTime) {
	if (currentState == GameState::PLAYING) 
	{
		player.update(deltaTime, map.getCollisionRects(), map);
		for (auto& e : enemies)
		{
			e->update(deltaTime, player.getPosition(), player);
		}

		enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& e) { return e->isDead(); }),enemies.end());

		// camera follows player
		sf::Vector2f playerPos = player.getPosition();
		cameraView.setCenter(playerPos);
		
		//win
		if (player.hasWon()) { 
			currentState = GameState::LEVEL_COMPLETE;
			levelManager.saveLevel(); // file handling
		}
		//lose
		else if (player.isDead()) {
			currentState = GameState::GAME_OVER;
		}
		//Level complete
		if (playerPos.x > map.getMapWidth() * map.getTileWidth() - 100) {
			levelManager.nextLevel();
			map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
			map.load();
			player.reset();
		}
		//if player is attacking
		if (player.isAttacking()) {
			std::cout << "Player is attacking \n";
			sf::FloatRect hitbox = player.getAttackHitbox();

			for (auto& enemy : enemies) {
				
				if (hitbox.intersects(enemy->getHitBox())) {
					enemy->takeDamage(); // or any value
					std::cout << "Enemy took damage\n";
				}
				//auto bounds = enemy->getBounds();
				//std::cout << "Enemy Bounds: " << bounds.left << ", " << bounds.top << ", " << bounds.width << ", " << bounds.height << "\n";
			}
		}
	}
}

void Game::render(sf::RenderWindow& window) {
	window.setFramerateLimit(60);
	window.clear();
	if (currentState == GameState::MENU)
	{
		window.setView(window.getDefaultView()); 
		menu.render(window);
	}
	else if (currentState == GameState::PLAYING)
	{
		window.setView(cameraView);
		// Draw background relative to camera
		backgroundSprite.setPosition(cameraView.getCenter().x - cameraView.getSize().x / 2,
			cameraView.getCenter().y - cameraView.getSize().y / 2);
		window.draw(backgroundSprite);
		map.draw(window);
		player.render(window, cameraView);
		for (auto& enemy : enemies)
		{
			enemy->render(window);
		//	std::cout << enemy->getBounds().width << "    "<< enemy->getBounds().height<< "  ";
		}
		player.renderHealthBar(window);

	}
	else if (currentState == GameState::PAUSED) {
		sf::Text pausedText("PAUSED - Press ESC to Resume", font, 30);
		pausedText.setPosition(cameraView.getCenter().x - 150, cameraView.getCenter().y);
		window.draw(pausedText);
	}
	else if (currentState == GameState::LEVEL_COMPLETE) {
		sf::Text winText("LEVEL COMPLETE - Press Enter", font, 30);
		winText.setPosition(cameraView.getCenter().x - 180, cameraView.getCenter().y);
		window.draw(winText);
	}
	else if (currentState == GameState::GAME_OVER) {
		sf::Text gameOverText("YOU DIED - Press Enter to Restart", font, 30);
		gameOverText.setPosition(cameraView.getCenter().x - 200, cameraView.getCenter().y);
		window.draw(gameOverText);
	}
	//ui.render(window);
	window.display();
}