#include "Menu.h"

void Menu::render(sf::RenderWindow& window) {
	
	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/HoldMoney-Regular.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
	}
	
	sf::Sprite bg;
	sf::Texture BGTexture;
	BGTexture.loadFromFile("Assets/MENU.png");
    bg.setTexture(BGTexture);
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2u textureSize = BGTexture.getSize();
	bg.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);

    sf::Text title("KINGDOM OF BURIA", font, 64);
    title.setFillColor(sf::Color(212, 175, 55)); // Golden
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(window.getSize().x / 2.f, 100);

    // Play Option
    sf::Text play("PLAY", font, 36);
    play.setFillColor(sf::Color::Black);
    sf::FloatRect playBounds = play.getLocalBounds();
    play.setOrigin(playBounds.width / 2, playBounds.height / 2);
    play.setPosition(window.getSize().x / 2.f, 200);

    sf::Text playHint("PRESS ENTER TO PLAY", font, 20);
    playHint.setFillColor(sf::Color::Black);
    sf::FloatRect phBounds = playHint.getLocalBounds();
    playHint.setOrigin(phBounds.width / 2, phBounds.height / 2);
    playHint.setPosition(window.getSize().x / 2.f, 240);

    // Continue Option
    sf::Text cont("CONTINUE", font, 36);
    cont.setFillColor(sf::Color::Black);
    sf::FloatRect contBounds = cont.getLocalBounds();
    cont.setOrigin(contBounds.width / 2, contBounds.height / 2);
    cont.setPosition(window.getSize().x / 2.f, 300);

    sf::Text contHint("PRESS C TO LOAD GAME", font, 20);
    contHint.setFillColor(sf::Color::Black);
    sf::FloatRect chBounds = contHint.getLocalBounds();
    contHint.setOrigin(chBounds.width / 2, chBounds.height / 2);
    contHint.setPosition(window.getSize().x / 2.f, 340);

    // Quit Option
    sf::Text quit("QUIT", font, 36);
    quit.setFillColor(sf::Color::Red);
    sf::FloatRect quitBounds = quit.getLocalBounds();
    quit.setOrigin(quitBounds.width / 2, quitBounds.height / 2);
    quit.setPosition(window.getSize().x / 2.f, 420);

	window.draw(bg);
    window.draw(title);
    window.draw(play);
    window.draw(playHint);
    window.draw(cont);
    window.draw(contHint);
   // window.draw(quit);

}