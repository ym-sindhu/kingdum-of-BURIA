#include "Menu.h"

void Menu::render(sf::RenderWindow& window) {
	
	sf::Font font;
	if (!font.loadFromFile("Assets/HoldMoney-Regular.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
	}
	
	sf::Sprite bg;
	sf::Texture BGTexture;
	BGTexture.loadFromFile("Assets/MENU.png");

	sf::Vector2u windowSize = window.getSize();
	sf::Vector2u textureSize = BGTexture.getSize();
	bg.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);

	bg.setTexture(BGTexture);
	sf::Text title("KINGDUM OF BURIA", font, 80);
	title.setPosition(100, 100);
	title.setFillColor(sf::Color::Yellow);

	sf::Text play("Play", font, 60);
	play.setPosition(300, 200);
	play.setFillColor(sf::Color::Black);

	sf::Text playText("Press Enter to Play", font, 20);
	playText.setFillColor(sf::Color::White);
	playText.setPosition(290, 270);

	sf::Text load("Continue", font, 60);
	load.setPosition(270, 300);
	load.setFillColor(sf::Color::Black);

	sf::Text quit("Quit", font, 60);
	quit.setPosition(300, 380);
	quit.setFillColor(sf::Color::Black);

	window.draw(bg);
	window.draw(title);
	window.draw(play);
	window.draw(playText);
	window.draw(load);
	window.draw(quit);
}