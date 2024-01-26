/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Direction
{
	None,
	Left,
	Right

};


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void processMouse(sf::Event t_event);
	
	void animate();
	void move();

	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game


	sf::Vector2f m_location{200.0f, 200.0f}; // location of helo
	sf::Vector2f m_velocity{0.0f, 0.0f};// helo velocity
	sf::Vector2f m_target{0.0f, 0.0f}; // target to travel to
	Direction m_direction{ Direction::None };

	sf::Texture m_heloTexture;// helo texture
	sf::Sprite m_heloSprite;// helo sprite
	float m_speed = 5.0f; // speed of helo 400mph

	int m_currentFrame = 0;// frame no
	float m_framecounter = 0.0f;// frame counter
	float m_frameIncrement = 0.25f;// frame increment 

	sf::SoundBuffer m_soundbuffer;// sound buffer
	sf::Sound m_sound;// sound object
};

#endif // !GAME_HPP

