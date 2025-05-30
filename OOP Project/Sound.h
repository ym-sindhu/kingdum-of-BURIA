#pragma once
#include <SFML/Audio.hpp>
#include "Global.h"
class SoundManager {
private:
    sf::Music menuMusic, playMusic, pauseMusic, gameOverMusic, levelCompleteMusic;
public:
    SoundManager() {}
    void playMusicForState(GameState state) {
        stopAllMusic();
        switch (state) {
        case GameState::MENU: menuMusic.setLoop(true); 
            menuMusic.play(); 
            std::cout << "MENU MUSIC PLAYING \n";
            break;
        case GameState::PLAYING: playMusic.setLoop(true); 
            playMusic.play(); 
            std::cout << "PLAY MUSIC PLAYING \n";
            break;
        case GameState::PAUSED: pauseMusic.setLoop(true); 
            pauseMusic.play(); 
            std::cout << "PAUSE MUSIC PLAYING \n";
            break;
        case GameState::GAME_OVER: gameOverMusic.setLoop(true); 
            gameOverMusic.play(); 
            std::cout << "GAMEOVER MUSIC PLAYING \n";
            break;
        case GameState::LEVEL_COMPLETE: levelCompleteMusic.setLoop(true); 
            levelCompleteMusic.play(); 
            std::cout << "LEVEL COMPLETE MUSIC PLAYING \n";
            break;
        }
    }

    void stopAllMusic() {
        menuMusic.stop();
        playMusic.stop();
        pauseMusic.stop();
        gameOverMusic.stop();
        levelCompleteMusic.stop();
        std::cout << "ALLLLL MUSICCCCCC STOPED !!!!!!!!!!!\n";

    }

    bool init() {
        try {
            if (!menuMusic.openFromFile("Sounds/menu_loop.ogg"))
                throw std::runtime_error("Failed to load menu_loop.ogg");

            if (!playMusic.openFromFile("Sounds/play_loop.ogg"))
                throw std::runtime_error("Failed to load play_loop.ogg");

            if (!gameOverMusic.openFromFile("Sounds/gameover_loop.ogg")) 
                throw std::runtime_error("Failed to load gameover_loop.ogg");

            if (!levelCompleteMusic.openFromFile("Sounds/levelcomplete_loop.ogg"))
                throw std::runtime_error("Failed to load levelcomplete_loop.ogg");


            menuMusic.setLoop(true);
            playMusic.setLoop(true);
            gameOverMusic.setLoop(true);
            levelCompleteMusic.setLoop(true);
        }
        catch (const std::exception& e) {
            std::cerr << "SoundManager initialization error: " << e.what() << std::endl;
        }
    }

};
