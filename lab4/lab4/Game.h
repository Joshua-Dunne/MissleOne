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
	bool m_hasClicked = false;
	bool m_drawBeam = false;
	bool m_drawExplosion = false;

	float m_asteroidSpeed = 5.0f;
	float m_beamSpeed = 5.0f;
	float m_explosionSize = 10.0f;
	float m_explosionDistance = 0.0f;
	float m_powerBarSize = 0.0f;
	float m_powerBarShot = 0.0f;
	const float m_POWERBARMAX = 300.0f;
	float m_distanceBetween = 0.0f;


	sf::RectangleShape m_ground;
	sf::RectangleShape m_player;
	sf::RectangleShape m_powerBar;

	sf::CircleShape m_beamExplosion{ m_explosionSize };

	sf::Vector2f m_beamLength{ 0.0f, 0.0f };
	sf::Vector2f m_beamNewLength{ 0.0f, 0.0f };
	sf::Vector2f m_beamPath{ 0.0f, 0.0f };
	sf::Vector2f m_maxAltitude{ 0.0f, 0.0f };
	sf::Vector2f m_unitVector{ 0.0f, 0.0f };
	sf::Vector2f m_explosionCentre{ 0.0f, 0.0f };


	sf::Vertex m_beamStart;
	sf::Vertex m_beamEnd;
	sf::Vertex m_beamEndCurrentPos;
	sf::VertexArray	m_beamLine{ sf::Lines };

	sf::Vertex m_enemyStart;
	sf::Vertex m_enemyEnd;
	sf::VertexArray	m_enemyLine{ sf::Lines };
};

#endif // !GAME

