// Author: Joshua Dunne
// C00241588
// Date(s): 22/11/18, 
// Estimated Time: 14 Hours
// Actual Time: ? Hours (CHANGE THIS)
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();
	void setupObjects();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_drawLines = false;
	bool m_hasClicked = false;

	float asteroidSpeed = 5.0f;
	float beamSpeed = 5.0f;

	sf::RectangleShape m_ground;
	sf::RectangleShape m_player;
	sf::RectangleShape m_powerBar;

	sf::Vector2f unitVector = { 0.0f, 0.0f };

	sf::Vertex m_beamStart;
	sf::Vertex m_beamEnd;
	sf::VertexArray	m_beamLine{ sf::Lines };

	sf::Vertex m_enemyStart;
	sf::Vertex m_enemyEnd;
	sf::VertexArray	m_enemyLine{ sf::Lines };
};

#endif // !GAME

