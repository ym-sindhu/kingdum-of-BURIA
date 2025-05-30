#include "Game.h"	
EnemyInfo level1Enemy = {
	"Assets/Enemies/Enemy_walk1.png",
	"Assets/Enemies/Enemy_attack1.png",
	"Assets/Enemies/Enemy_death1.png",
	34, 63, 128, 65,
	10, 4, 5,
	0.2f, 0.1f, 0.1f
};

EnemyInfo level1Boss = {
	"Assets/Boss/boss_walk1.png",
	"Assets/Boss/boss_attack1.png",
	"Assets/Boss/boss_death1.png",
	80, 44 ,250,124,
	8, 8, 7,
	0.2f ,0.2f, 0.2f
};

EnemyInfo level2Enemy = {
	"Assets/Enemies/Enemy_walk2.png",
	"Assets/Enemies/Enemy_attack2.png",
	"Assets/Enemies/Enemy_death2.png",
	34, 63, 128, 65,
	10, 5, 5,
	0.2f, 0.1f, 0.1f
};

EnemyInfo level2Boss = {
	"Assets/Boss/boss_walk2.png",
	"Assets/Boss/boss_attack2.png",
	"Assets/Boss/boss_death2.png",
	30, 13 ,100,63,
	4, 6, 10,
	0.2f ,0.2f, 0.2f
};

EnemyInfo level3Enemy1 = {
	"Assets/Enemies/Enemy_walk2.png",
	"Assets/Enemies/Enemy_attack2.png",
	"Assets/Enemies/Enemy_death2.png",
	34, 63, 128, 65,
	10, 5, 5,
	0.2f, 0.1f, 0.1f
};

EnemyInfo level3Enemy2 = {
	"Assets/Enemies/Enemy_walk1.png",
	"Assets/Enemies/Enemy_attack1.png",
	"Assets/Enemies/Enemy_death1.png",
	34, 63, 128, 65,
	10, 4, 5,
	0.2f, 0.1f, 0.1f
};

EnemyInfo level3Boss = {
	"Assets/Boss/boss_walk3.png",
	"Assets/Boss/boss_attack3.png",
	"Assets/Boss/boss_death3.png",
	20, 13 ,80,67,
	6, 12, 23,
	0.2f ,0.2f, 0.2f
};

Game::Game() : window(sf::VideoMode(800, 600), "Kingdum of Buria"), currentState(GameState::MENU)
{
	if (!font.loadFromFile("Assets/Fonts/HoldMoney-Regular.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
	}
	soundManager.init();
	soundManager.playMusicForState(currentState);
}

void Game::run() {
	sf::Clock clock;
	cameraView.setSize(800, 600); // same as window
	cameraView.setCenter(player.getPosition());


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
		{
			soundManager.stopAllMusic();
			window.close();
		}
		if (currentState == GameState::MENU && event.type == sf::Event::KeyPressed) 
			if (event.key.code == sf::Keyboard::Enter) 
			{   //soundManager
				levelManager.setLevel(1); // New Game
				levelManager.saveLevel();
				level = levelManager.getLevel();
				levelFinished = false;
				loadBG(levelManager.getLevel());
				map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
				map.load();
				loadEnemies(1);
				float obeliskX = (map.getMapWidth() - 3) * map.getTileWidth();
				float obeliskY = (map.getMapHeight() - 1) * map.getTileHeight();
				sf::Vector2f obeliskPos(obeliskX, obeliskY - 170);
				obelisk = std::make_unique<Obelisk>(obeliskPos);

				currentState = GameState::PLAYING;
				soundManager.playMusicForState(currentState);
			}
			else if (event.key.code == sf::Keyboard::C) {
				levelManager.loadSavedLevel(); // Continue
				map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
				map.load();
				player.reset();
				currentState = GameState::PLAYING;
				soundManager.playMusicForState(currentState);
			}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
		{
			if (currentState == GameState::PLAYING)
				currentState = GameState::PAUSED;
			else if (currentState == GameState::PAUSED)
				currentState = GameState::PLAYING;
			soundManager.playMusicForState(currentState);
		}
		if (currentState == GameState::LEVEL_COMPLETE && event.key.code == sf::Keyboard::Enter) {
			soundManager.playMusicForState(currentState);
			levelManager.nextLevel(); 

		if(levelManager.getLevel() > 3)
		{
			soundManager.playMusicForState(currentState);
			currentState = GameState::FINISH;
		}else 
		{
			loadBG(levelManager.getLevel());
			map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
			map.load();
			loadEnemies(levelManager.getLevel());
			player.reset();
			float obeliskX = (map.getMapWidth() - 3) * map.getTileWidth();
			float obeliskY = (map.getMapHeight() - 1) * map.getTileHeight();
			sf::Vector2f obeliskPos(obeliskX, obeliskY - 170);
			obelisk = std::make_unique<Obelisk>(obeliskPos);
			currentState = GameState::PLAYING;
			soundManager.playMusicForState(currentState);
		}
		}
		if (currentState == GameState::GAME_OVER && event.key.code == sf::Keyboard::Enter) {
			soundManager.playMusicForState(currentState);
			levelManager.setLevel(1);
			map.open(levelManager.getMapFilename(), levelManager.getMapTextureName(), 96, 96);
			player.reset();
			currentState = GameState::PLAYING;
			soundManager.playMusicForState(currentState);
		}if (currentState == GameState::FINISH) {
			soundManager.playMusicForState(currentState);
			currentState = GameState::FINISH;
			soundManager.playMusicForState(currentState);
		}
		
	}
}

void Game::loadEnemies(int levelNumber)
{
	enemies.clear();
	std::cout << "Spawning enemies for level: " << levelManager.getLevel() << std::endl;

	if (levelManager.getLevel() == 1) {
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
		///std::cout << "Enemy size : " << enemies.size();
		auto boss = std::make_unique<Boss>(
			level1Boss,
			sf::Vector2f(1400, 200),
			1000,
			40.f
		);
		boss->setscale(1.5f, 1.5f);
		enemies.push_back(std::move(boss));
		
	}
	else if (levelManager.getLevel() == 2) {
		std::cout << "Pushing back enemies for level : " << levelManager.getLevel() << "\n";
		enemies.push_back(std::make_unique<NormalEnemy>(
			level2Enemy,// texture path
			sf::Vector2f(500, 312),           // position
			15.f,                             // speed
			100.f,                            // patrol range
			true
		));
		enemies.push_back(std::make_unique<NormalEnemy>(
			level2Enemy,
			sf::Vector2f(800, 312),
			15.f,
			100.f,
			true
		));
		enemies.push_back(std::make_unique<NormalEnemy>(
			level2Enemy,
			sf::Vector2f(1000, 312),
			15.f,
			100.f,
			true
		));
		auto boss = std::make_unique<Boss>(
			level2Boss,
			sf::Vector2f(1400, 270),
			1000,
			40.f
		);
		boss->setscale(2.0f, 2.0f);
		enemies.push_back(std::move(boss));
	}
	else if (levelManager.getLevel() == 3) {
		std::cout << "Pushing back enemies for level : " << levelManager.getLevel() << "\n";
		enemies.push_back(std::make_unique<NormalEnemy>(
			level3Enemy1,// texture path
			sf::Vector2f(500, 312),           // position
			15.f,                             // speed
			100.f,                            // patrol range
			true
		));
		enemies.push_back(std::make_unique<NormalEnemy>(
			level3Enemy1,
			sf::Vector2f(800, 312),
			15.f,
			100.f,
			true
		));
		enemies.push_back(std::make_unique<NormalEnemy>(
			level3Enemy2,
			sf::Vector2f(1000, 312),
			15.f,
			100.f,
			true
		));
		enemies.push_back(std::make_unique<NormalEnemy>(
			level3Enemy2,
			sf::Vector2f(1300, 312),
			15.f,
			100.f,
			true
		));
		auto boss = std::make_unique<Boss>(
			level3Boss,
			sf::Vector2f(2000, 230),
			1000,
			40.f
		);
		boss->setscale(3.0f, 3.0f);
		enemies.push_back(std::move(boss));
		
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
			e->update(deltaTime, player.getPosition(), player);
		
		if (obelisk)
			obelisk->update(deltaTime);

		enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& e) { return e->isDead(); }),enemies.end());

		// camera follows player
		sf::Vector2f playerPos = player.getPosition();
		cameraView.setCenter(playerPos);
		
		//win
		if (enemies.empty() && player.getBounds().intersects(obelisk->getBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			currentState = GameState::LEVEL_COMPLETE;
			soundManager.playMusicForState(currentState);
		    std::cout << "Level Complete!\n";
			levelManager.saveLevel(); // file handling
		}
		//lose 
		else if (player.isDead()) {
			currentState = GameState::GAME_OVER;
			soundManager.playMusicForState(currentState);
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
		if (obelisk)
			obelisk->render(window);
		player.render(window, cameraView);
		for (auto& enemy : enemies)
			enemy->render(window);
		
		player.renderHealthBar(window);

	}
	else if (currentState == GameState::PAUSED) {
		sf::Text pausedText("PAUSED - Press ESC to Resume", font, 30);
		pausedText.setPosition(cameraView.getCenter().x - 150, cameraView.getCenter().y);
		window.draw(pausedText);
	}
	else if (currentState == GameState::LEVEL_COMPLETE) {
		sf::Text winText("LEVEL COMPLETE - Press Enter to Continue", font, 30);
		winText.setPosition(cameraView.getCenter().x - 180, cameraView.getCenter().y);
		obelisk = nullptr;
		window.draw(winText);
	}
	else if (currentState == GameState::GAME_OVER) {
		sf::Text gameOverText("YOU DIED - Press Enter to Restart", font, 30);
		gameOverText.setPosition(cameraView.getCenter().x - 200, cameraView.getCenter().y);
		obelisk = nullptr;
		window.draw(gameOverText);
	}
	else if (currentState == GameState::FINISH)
	{
		sf::Text fin("Game Finished\nCongratulations\nYOU WIN!", font, 40);
		fin.setPosition(cameraView.getCenter().x - 200, cameraView.getCenter().y);
		obelisk = nullptr;
		window.draw(fin);
	}
	//ui.render(window);
	window.display();
}