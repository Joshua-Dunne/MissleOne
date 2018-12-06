// Author: Joshua Dunne
// C00241588
// Date(s): 22/11/18, 26/11/18, 29/11/18, 30/11/18, 02/12/18, 04/12/18, 06/12/18
// Estimated Time: 14 Hours
// Actual Time: 12 Hours (CHANGE THIS)
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
	void findPlayerClick(sf::Event t_mouse);
	void findNewEnemyPosition();
	void fireBeam();
	void spawnExplosion();
	void moveAsteroid();
	void powerBarControl();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_scoreText; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_hasClicked = false; // Checks if the User has clicked.
	bool m_drawBeam = false; // Checks if the beam should be drawn.
	bool m_drawExplosion = false; // Checks if the explosion should be drawn.
	bool m_drawEnemy = true;
	bool m_findNewEnemyPosition = false;
	bool m_hasGainedScore = false;

	sf::RectangleShape m_testExplosionCentre;

	float m_asteroidSpeed = 0.5f; // The Speed of the Asteroid (enemy).
	float m_beamSpeed = 0.20f; // The Speed of the Player's Laser.
	float m_explosionSize = 10.0f; // The initial size of the Explosion.
	float m_powerBarSize = 0.0f; // The initial size of the Power Bar
	float m_powerBarShot = 0.0f; // Will be used later to determine the altitude
	const float m_POWERBAR_MAX = 200.0f; // The Maximum Size the Power Bar can go to.
	const float m_EXPLOSION_MAX = 25.0f;
	float m_altitude = 0.0f;
	float m_distanceBetween = 0.0f; // The Distance between the Asteroid and the Explosion's Centre.
	int enemyCooldown = 1; // How long it takes for the asteroid to come back.
	int score = 0;


	sf::RectangleShape m_ground; // Shows the player where the asteroid shouldn't go.
	sf::RectangleShape m_player; // It's you!
	sf::RectangleShape m_powerBar; // The Power Bar. Original content. Don't steal.

	sf::CircleShape m_beamExplosion{ m_explosionSize }; // The big bang.

	sf::Vector2f m_beamLength{ 0.0f, 0.0f }; // The length of the original beam.
	sf::Vector2f m_beamNewLength{ 0.0f, 0.0f }; // The length of the beam that is updated with a new end point.
	sf::Vector2f m_maxAltitude{ 0.0f, 0.0f }; // Will be used later to determine how far the player's beam can go.
	sf::Vector2f m_unitVector{ 0.0f, 0.0f }; // Holds the Unit Vector value.
	sf::Vector2f m_explosionCentre{ 0.0f, 0.0f }; // Holds the position of the centre of the explosion.

	sf::Vector2f m_enemyBeamLength{ 0.0f, 0.0f }; // The length of the enemy's original beam.
	sf::Vector2f m_enemyBeamNewLength{ 0.0f, 0.0f }; // The length of the enemy's beam that is updated with a new end point.
	sf::Vector2f m_enemyUnitVector{ 0.0f, 0.0f }; // Holds the enemy's Unit Vector value.


	sf::Vertex m_beamStart; // The start of the player's beam (Always at the player).
	sf::Vertex m_beamEnd; // The end of the player's beam (Where the player clicks).
	sf::Vertex m_beamEndCurrentPos; // The new end of the player's beam (Helps increment the beam).
	sf::VertexArray	m_beamLine{ sf::Lines }; // Holds the Start and End positions for the player and draws a line between them.

	sf::Vertex m_enemyStart; // The start of the enemy's beam (Currently always at the top centre.)
	sf::Vertex m_enemyEnd; // The end of the enemy's beam (Where it decides to go).
	sf::Vertex m_enemyEndCurrentPos; // The new end of the enemy's beam (Helps increment the beam).
	sf::VertexArray	m_enemyLine{ sf::Lines }; // Holds the Start and End positions for the enemy and draws a line between them.
};

#endif // !GAME

