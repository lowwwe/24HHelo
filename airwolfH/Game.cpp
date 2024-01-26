/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouse(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	animate();
	move();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_heloSprite);
	m_window.display();
}

void Game::processMouse(sf::Event t_event)
{
	sf::Vector2f heading{0.0f, 0.0f}; // flight path
	float lenght;
	m_target.x = static_cast<float>( t_event.mouseButton.x);
	m_target.y = static_cast<float>(t_event.mouseButton.y);
	heading = m_target - m_location ;
	if (heading.x < 0)
	{
		m_direction = Direction::Left;
		m_heloSprite.setScale(-1.0f, 1.0f);
	}
	else
	{
		m_direction = Direction::Right;
		m_heloSprite.setScale(1.0f, 1.0f);
	}
	lenght = std::sqrtf( heading.x * heading.x + heading.y * heading.y);
	m_velocity = heading / lenght;
	m_velocity = m_velocity * m_speed;
	m_sound.setPitch(1.0f);

}

void Game::animate()
{
	int lastFrame = m_currentFrame;
	m_framecounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_framecounter) % 4;
	if (lastFrame != m_currentFrame)
	{
		m_heloSprite.setTextureRect(sf::IntRect{0, m_currentFrame * 64, 180, 64});
		// frame one m_heloSprite.setTextureRect(sf::IntRect{0, 0, 180, 64});
		// frame two m_heloSprite.setTextureRect(sf::IntRect{0, 64, 180, 64});
		// frame three m_heloSprite.setTextureRect(sf::IntRect{0, 128, 180, 64});
		// frame four  m_heloSprite.setTextureRect(sf::IntRect{0, 196, 180, 64});
	}
}

void Game::move()
{
	if (m_direction != Direction::None)
	{
		m_location += m_velocity;


		if (Direction::Left == m_direction &&
			m_target.x > m_location.x)
		{
			m_direction = Direction::None;
			m_sound.setPitch(0.5f);
		}
		if (Direction::Right == m_direction &&
			m_target.x < m_location.x)
		{
			m_direction = Direction::None;
			m_sound.setPitch(0.5f);
		}
	}

	m_heloSprite.setPosition(m_location);
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);

	if (!m_heloTexture.loadFromFile("ASSETS\\IMAGES\\helicopter.png"))
	{
		std::cout << "error message";
	}
	m_heloSprite.setTexture(m_heloTexture);
	m_heloSprite.setPosition(m_location);
	m_heloSprite.setTextureRect(sf::IntRect{0, 0, 180, 64});
	m_heloSprite.setOrigin(90.0f, 32.0f);

	m_soundbuffer.loadFromFile("ASSETS\\SOUNDS\\helicopter.wav");
	m_sound.setBuffer(m_soundbuffer);
	m_sound.play();
	m_sound.setPitch(0.5f);
	m_sound.setLoop(true);
}
