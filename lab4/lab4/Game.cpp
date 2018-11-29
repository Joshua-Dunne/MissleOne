// Author: Joshua Dunne
// C00241588
// Date(s): 22/11/18, 
// Estimated Time: 14 Hours
// Actual Time: ? Hours (CHANGE THIS)

#include "Game.h"
#include  "MyVector2.h"
#include <iostream>


/// <summary>
/// default construcor
/// pass parameters fpr sfml window, setup m_exitGame
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupObjects(); // Sets up Ground/Player objects.
}

/// <summary>
/// default destructor for game, nothing to release
/// </summary>
Game::~Game()
{
}


/// <summary>
/// game loop running at 60fps
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

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
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		if (sf::Mouse::Left == event.mouseButton.button && event.mouseButton.y < 500) // If the left mouse button is pressed..
		{
			if (m_hasClicked == false) {
				m_beamLine.clear();
				m_beamLine.append(m_beamStart);
				m_beamEnd.position = static_cast<sf::Vector2f>((sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
				m_beamLength = m_beamEnd.position - m_beamStart.position;
				m_unitVector = vectorUnitVector(m_beamLength);
				m_hasClicked = true;	
				m_drawBeam = true;
				m_powerBarShot = m_powerBarSize;
				m_powerBarSize = 0.0f;
				m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 50.0f));
			}
		}

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

	if (m_powerBarSize < m_POWERBARMAX && m_hasClicked == false) {
		m_powerBarSize += 0.5;
		m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 50.0f));
		//m_powerBarShot = m_powerBarSize 
	}
	

	if (m_drawBeam == true)
	{
		m_beamLine.clear();
		m_beamLine.append(m_beamStart);
		m_beamEndCurrentPos.position += (m_unitVector * (m_beamSpeed + 5));
		m_beamLine.append(m_beamEndCurrentPos);
		//m_maxAltitude = m_beamEnd.position.y / 
		

		if (m_beamEndCurrentPos.position.y < m_beamEnd.position.y)
		{
			m_drawExplosion = true;
			m_beamExplosion.setPosition(m_beamEnd.position.x - m_explosionSize, m_beamEnd.position.y - m_explosionSize);
			m_beamEndCurrentPos.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
			m_beamPath = { 0.0f, 0.0f };
			m_beamLine.clear();
			m_drawExplosion = true;
			m_drawBeam = false;
		}
	}

	if (m_drawExplosion == true)
	{
		m_explosionSize += 0.2f;
		m_beamExplosion.setRadius(m_explosionSize);
		m_beamExplosion.setPosition(m_beamEnd.position.x - m_explosionSize, m_beamEnd.position.y - m_explosionSize);
		m_explosionCentre = sf::Vector2f(m_beamExplosion.getPosition().x + m_explosionSize, m_beamExplosion.getPosition().y + m_explosionSize);

		m_distanceBetween = vectorLength(m_enemyEnd.position - m_explosionCentre);

		if (m_distanceBetween < m_explosionSize)
		{
			std::cout << "Enemy hit!";
		}

		if (m_explosionSize >= 25.0f)
		{
			m_drawExplosion = false;
			m_beamExplosion.setPosition(-1000.0f, -1000.0f);
			m_explosionSize = 10.0f;
			m_hasClicked = false;
		}
	}

}


/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	m_window.draw(m_ground);
	m_window.draw(m_enemyLine);
	m_window.draw(m_player);
	m_window.draw(m_powerBar);

	if (m_drawBeam == true)
	{
		m_window.draw(m_beamLine);

	}

	if (m_drawExplosion == true)
	{
		m_window.draw(m_beamExplosion);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	/*
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Pete is Cool");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::White);
	m_welcomeMessage.setOutlineThickness(3.0f);
	*/
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

	/*
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
	*/
}

void Game::setupObjects()
{
	// Sets up Ground
	m_ground.setSize(sf::Vector2f(800.0f, 100.0f));
	m_ground.setPosition(sf::Vector2f(0.0f, 500.0f));
	m_ground.setFillColor(sf::Color::Green);

	// Sets up the "Player"
	m_player.setSize(sf::Vector2f(50.0f, 50.0f));
	m_player.setPosition(sf::Vector2f((m_window.getSize().x / 2) - (m_player.getSize().x / 2), 450.0f));
	m_player.setFillColor(sf::Color::Red);

	// Sets up the Power Bar
	m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 50.0f));
	m_powerBar.setPosition(sf::Vector2f(50.0f, 525.0f));
	m_powerBar.setFillColor(sf::Color::Red);

	// Sets up the player's beam
	m_beamStart.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
	m_beamStart.color = sf::Color::Yellow; // Sets the color of that point to yellow.
	m_beamEnd.color = sf::Color::Yellow; // Sets the color of that point to yellow, making the entire line Yellow.
	m_beamEndCurrentPos.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
	m_beamEndCurrentPos.color = sf::Color::Yellow; // Sets the color of that point to yellow, making the entire line Yellow.
	m_beamLine.append(m_beamStart); // Initially appends the beamStart

	// Sets up the enemy's beam
	m_enemyStart.position = (sf::Vector2f(400.0f, 0.0f));
	m_enemyEnd.position = (sf::Vector2f(400.0f, 300.0f));
	m_enemyStart.color = sf::Color::Blue;
	m_enemyEnd.color = sf::Color::Blue;
	m_enemyLine.append(m_enemyStart);
	m_enemyLine.append(m_enemyEnd);
	// All enemy stuff is pre-determined for the time being.

	// Sets up explosion that appears at end of beam.
	m_beamExplosion.setFillColor(sf::Color::Red);
	m_beamExplosion.setRadius(m_explosionSize);
	
}	