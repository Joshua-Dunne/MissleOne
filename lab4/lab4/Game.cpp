// Author: Joshua Dunne
// C00241588
// Date(s): 22/11/18, 26/11/18, 29/11/18, 30/11/18
// Estimated Time: 14 Hours
// Actual Time: ? Hours (CHANGE THIS)

#include "Game.h"
#include "MyVector2.h"
#include <iostream>
#include <stdlib.h>


/// <summary>
/// default construcor
/// pass parameters for sfml window, setup m_exitGame
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

		if (sf::Mouse::Left == event.mouseButton.button && event.mouseButton.y < 500)
		{// If the left mouse button is pressed and their mouse is above 100px...
			if (m_hasClicked == false) { // If the Player hasn't clicked yet
				m_beamLine.clear(); // Clear any existing vertices in the Vertex Array.
				m_beamLine.append(m_beamStart); // Immediately append the start vertex, as it's never going to change.
				m_beamEnd.position = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
				// Set the beamEnd's position to where the user clicked, and use a static cast to avoid conversion warnings.
				m_beamLength = m_beamEnd.position - m_beamStart.position;
				// Get the line between two points.
				m_unitVector = vectorUnitVector(m_beamLength);
				// Get the unit vector of that line.
				m_hasClicked = true; // The player has now clicked.
				m_drawBeam = true; // Draw the player's beam.
				m_powerBarSize = 0.0f; // Reset the size of the Power Bar.
				m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 50.0f)); // Make the change.
				
			}
		}
#ifdef  _DEBUG
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			findNewEnemyPosition();
		}
#endif //  _DEBUG
	}
}
/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame) // Is true when the player presses Escape.
	{
		m_window.close(); // Bye
	}

	if (m_powerBarSize < m_POWERBAR_MAX && m_hasClicked == false) {
		// If the Power Bar hasn't reached it's max size and the user has not clicked..
		m_powerBarSize += 0.5; // Increase the size by 0.5f.
		m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 50.0f)); // Make the change.
		m_altitude = 500.0f - (m_powerBarSize * 2);
	}
	
	//if (m_drawEnemy == true) {
	if (m_drawEnemy == true) {
		if (m_enemyBeamLength.x > 800 || m_enemyBeamLength.y > 600) { // If the enemy's start position is off screen-ish
			m_enemyStart.position = (sf::Vector2f(static_cast<float>(rand() % 800), 0.0f)); // Get a new position
			m_enemyEnd.position = sf::Vector2f(static_cast<float>(rand() % 800), 600.0f); // Get a new position
			m_enemyBeamLength = m_enemyEnd.position - m_enemyStart.position; // Get the line
		}
		else { // Carry on with calculations
			m_enemyUnitVector = vectorUnitVector(m_enemyBeamLength); // Get the vector unit of the line
			m_enemyLine.clear(); // Clear any original vertices within the Vertex Array.
			m_enemyLine.append(m_enemyStart); // Append the start point first.
			m_enemyEndCurrentPos.position += (m_enemyUnitVector * (m_asteroidSpeed)); // Find the new position for the end point.
			m_enemyLine.append(m_enemyEndCurrentPos); // Append it to the Vertex Array.
		}
	}
	//}

	if (m_enemyEndCurrentPos.position.y > 500)
	{
		findNewEnemyPosition(); // If the enemy's new end position goes below 500px, generate a new line.
		// This is temporary as the player is meant to lose, but I will implement it later.
	}

	if (m_drawBeam == true)
	{ 
		fireBeam();
	}

	if (m_drawExplosion == true)
	{
		m_explosionSize += 0.2f; // Increment the size of the explosion

		m_beamExplosion.setRadius(m_explosionSize); // Make the explosion bigger

		m_explosionCentre = sf::Vector2f(m_beamExplosion.getPosition().x + m_explosionSize, m_beamExplosion.getPosition().y + m_explosionSize);
		// Finds the explosion's centre.
		// Adds the explosion size because the origin of a CircleShape is at the top left, and we want to find the center of it.

		m_distanceBetween = vectorLength(sf::Vector2f(m_enemyEndCurrentPos.position) - m_explosionCentre);
		// Gets the length of the distance between the enemy's end position and the explosion's centre.

		if (m_distanceBetween < m_explosionSize && m_drawEnemy == true) // If the distance between is less than the explosion's radius..
		{
			enemyCooldown = (rand() % 40) + 60;
			m_enemyLine.clear();
			m_drawEnemy = false;
			m_findNewEnemyPosition = true;
		} 

		if (m_explosionSize >= m_EXPLOSION_MAX) // Once the explosion reaches it's max size..
		{
			m_drawExplosion = false; // Stop drawing it
			m_explosionSize = 10.0f; // Put it's size back to normal.
			m_hasClicked = false; // Let the user click again.
		}
	}

	if (m_findNewEnemyPosition == true)
	{
		enemyCooldown--;
	}

	if (enemyCooldown < 1)
	{
		m_findNewEnemyPosition = false;
		findNewEnemyPosition();
		enemyCooldown = 1;
	}

}


/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_ground);
	m_window.draw(m_enemyLine);
	m_window.draw(m_player);
	m_window.draw(m_powerBar);

	if (m_drawBeam == true) // Only draw the beam when you need it.
	{
		m_window.draw(m_beamLine);

	}

	if (m_drawExplosion == true) // Only draw the explosion when you need it.
	{
		m_window.draw(m_beamExplosion);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{ // Will be used to set up font and text for a Score.
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
{ // Will be used to draw some sprites for the player.

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
{ // Initializes all necessary sprites/lines.
	// Sets up Ground
	m_ground.setSize(sf::Vector2f(800.0f, 100.0f)); // Makes the ground the length of the screen.
	m_ground.setPosition(sf::Vector2f(0.0f, 500.0f)); // Puts the ground at the bottom of the screen.
	m_ground.setFillColor(sf::Color::Green); // It's Green now.

	// Sets up the "Player"
	m_player.setSize(sf::Vector2f(50.0f, 50.0f)); // Set's the "Player"'s size.
	m_player.setPosition(sf::Vector2f((m_window.getSize().x / 2) - (m_player.getSize().x / 2), 450.0f)); 
	// Sets the "Player"'s position to above the ground.
	m_player.setFillColor(sf::Color::Red); // It's Red now.

	// Sets up the Power Bar
	m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 50.0f)); // Sets the Power Bar's size
	m_powerBar.setPosition(sf::Vector2f(50.0f, 525.0f)); // Sets the position of the Power Bar so it's in the ground.
	m_powerBar.setFillColor(sf::Color::Red); // It's also Red now.

	// Sets up the player's beam
	m_beamStart.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
	m_beamStart.color = sf::Color::Yellow; // Sets the color of that point to yellow.
	m_beamEnd.color = sf::Color::Yellow; // Sets the color of that point to yellow, making the entire line Yellow.
	m_beamEndCurrentPos.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
	m_beamEndCurrentPos.color = sf::Color::Yellow; // Sets the color of that point to yellow, making the entire line Yellow.
	m_beamLine.append(m_beamStart); // Initially appends the beamStart

	// Sets up the enemy's beam
	m_enemyStart.color = sf::Color::Blue;
	m_enemyEnd.color = sf::Color::Blue;
	m_enemyEndCurrentPos.color = sf::Color::Blue;
	m_enemyStart.position = (sf::Vector2f(static_cast<float>(rand() % 800), 0.0f));
	m_enemyEndCurrentPos.position = m_enemyStart.position;
	m_enemyEnd.position = sf::Vector2f(static_cast<float>(rand() % 800), 300);
	m_enemyBeamLength = m_enemyEnd.position + m_enemyStart.position;
	m_enemyUnitVector = vectorUnitVector(m_enemyBeamLength);

	// All enemy stuff is pre-determined for the time being.

	// Sets up explosion that appears at end of beam.
	m_beamExplosion.setFillColor(sf::Color::Red);
	m_beamExplosion.setRadius(m_explosionSize);
	m_beamExplosion.setOrigin(m_explosionSize, m_explosionSize);
	
}	

void Game::findNewEnemyPosition()
{ // A function that gets a new position for the asteroid.
	m_enemyLine.clear(); // Clears the line
	m_enemyStart.position = (sf::Vector2f(static_cast<float>(rand() % 800), 0.0f)); // Get a new start position
	m_enemyEndCurrentPos.position = m_enemyStart.position; // Start the new end position at the start position.
	m_enemyEnd.position = sf::Vector2f(static_cast<float>(rand() % 800), 600); // Get a new end position
	m_enemyBeamLength = m_enemyEnd.position - m_enemyStart.position; // Get the line
	m_enemyUnitVector = vectorUnitVector(m_enemyBeamLength); // Get the unit vector of that line
	m_drawEnemy = true;
}

void Game::fireBeam() 
{ // A function that increments the player's beam step by step, and spawns a circle at the end of the path.
	m_beamLine.clear(); // Clear any original vertices within the Vertex Array.
	m_beamLine.append(m_beamStart); // Immediately append the start position, since it's going to be the same all the time.
	m_beamEndCurrentPos.position += (m_unitVector * (m_beamSpeed + 5)); // Find the new position for the end point.
	m_beamLine.append(m_beamEndCurrentPos); // Append it to the Vertex Array.
	//m_maxAltitude = m_beamEnd.position.y / 

	if (m_beamEndCurrentPos.position.y <= m_altitude)
	{
		m_drawExplosion = true; // Draw the explosion
		m_drawBeam = false; // Stop drawing the beam.
		m_beamExplosion.setPosition(m_beamEndCurrentPos.position.x, m_beamEndCurrentPos.position.y);
		// Set the explosion's position.
		m_beamLine.clear(); // Clear the Vertex Array
		m_beamEndCurrentPos.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
	}

	if (m_beamEndCurrentPos.position.y <= m_beamEnd.position.y)
	{ // Once the new End Position reaches the same Y position as the old End Position
		m_drawExplosion = true; // Draw the explosion
		m_beamExplosion.setPosition(m_beamEnd.position.x, m_beamEnd.position.y);
		// Set the explosion's position.
		m_beamLine.clear(); // Clear the Vertex Array
		m_beamEndCurrentPos.position = (sf::Vector2f(400.0f, 500.0f)); // Puts the beam's initial position to where the player is.
		m_drawBeam = false; // Stop drawing the beam.
	}

}