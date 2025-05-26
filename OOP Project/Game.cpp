#include "Game.h"	

Game::Game() : window(sf::VideoMode(800, 600), "Kingdum of Buria"), currentState(GameState::MENU), map("Assets/Maps/level1.tmj", "Assets/Maps/Tiles.png", 96, 96) {}

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
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (currentState == GameState::MENU && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
			currentState = GameState::PLAYING;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
		{
			if (currentState == GameState::PLAYING)
				currentState = GameState::PAUSED;

			else if (currentState == GameState::PAUSED)
				currentState = GameState::PLAYING;
		}
	}
}

void Game::update(float deltaTime) {
	if (currentState == GameState::PLAYING) 
	{
		player.update(deltaTime, map.getCollisionRects(), map);
		
		// camera follows player
		sf::Vector2f playerPos = player.getPosition();
		cameraView.setCenter(playerPos);
		std::cout << "Camera Center: " << cameraView.getCenter().x << ", " << cameraView.getCenter().y << std::endl;

	}
}

void Game::render(sf::RenderWindow& window) {
	window.setFramerateLimit(60);
	window.clear();
	if (currentState == GameState::MENU)
	{
		window.setView(window.getDefaultView()); // reset view
		menu.render(window);
	}
	else if (currentState == GameState::PLAYING)
	{
		window.setView(cameraView);
		map.draw(window);
		player.render(window, cameraView);
	}
	//ui.render(window);
	window.display();
}