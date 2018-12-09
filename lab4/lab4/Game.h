// Author: Joshua Dunne
// C00241588
// Date(s): 22/11/18, 26/11/18, 29/11/18, 30/11/18, 02/12/18, 04/12/18, 06/12/18, 07/12/18, 09/12/18
// Estimated Time: 14 Hours
// Actual Time: 16 Hours

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	void setupSprite(); // Sets up any Sprites.
	void setupObjects(); // Sets up any game objects.
	void setupAudio();
	void findPlayerClick(sf::Event t_mouse); // Find where the player clicked.
	void findNewEnemyPosition(); // Find a new position for the enemy.
	void fireBeam(); // Find the beam's path and increment it bit by bit.
	void spawnExplosion(); // Spawn an explosion at the end of the beam.
	void moveAsteroid(); // Find the enemy's path and increment it bit by bit.
	void powerBarControl(); // Controls Power Bar and determines max altitude for player's beam
	void restartGame(); // Refreshes the game's score, powerbar, enemy positions and beam positions.

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_scoreText; // Text used to display score
	sf::Text m_gameOverText; // Text used to show when the player has lost

	//----------------------------------------------------------------------------------- EXTRA FEATURES
	sf::Text m_extrasText; // Text used to show the player they're using Extra Features.
	sf::Texture m_groundTexture; // Texture for the Ground
	sf::Texture m_playerTexture; // Texture for the Player
	sf::Texture m_backgroundTexture; // Texture for Background
	sf::Sprite m_groundSprite; // Ground Sprite
	sf::Sprite m_playerSprite; // Player Sprite
	sf::Sprite m_background; // Background Sprite
	sf::SoundBuffer m_playerBeamBuffer; // Sound Buffer for the Player's Beam
	sf::SoundBuffer m_explosionSoundBuffer; // Sound Buffer for the Explosion
	sf::Sound m_playerBeamSound; // Plays when the Player shoots their laser.
	sf::Sound m_explosionSound; // Plays when an explosion happens.
	sf::Music m_backgroundMusic; // Background music
	//----------------------------------------------------------------------------------- EXTRA FEATURES
	bool m_exitGame; // control exiting game
	bool m_hasClicked = false; // Checks if the User has clicked.
	bool m_drawBeam = false; // Checks if the beam should be drawn.
	bool m_drawExplosion = false; // Checks if the explosion should be drawn.
	bool m_drawEnemy = true; // Checks to see if the enemy should be drawn.
	bool m_findNewEnemyPosition = false; // Checks to see if the enemy needs a new start position.
	bool m_hasGainedScore = false; // Checks to see if the player has gained score.
	bool m_playerIsDead = false; // Checks to see if the game is over.
	bool m_extraFeatures = false;

	sf::RectangleShape m_testExplosionCentre;

	float m_asteroidSpeed = 0.5f; // The Speed of the Asteroid (enemy).
	float m_beamSpeed = 3.0f; // The Speed of the Player's Laser.
	float m_explosionSize = 10.0f; // The initial size of the Explosion.
	float m_powerBarSize = 0.0f; // The initial size of the Power Bar
	float m_powerBarShot = 0.0f; // Will be used later to determine the altitude
	const float m_POWERBAR_MAX = 200.0f; // The Maximum Size the Power Bar can go to.
	const float m_EXPLOSION_MAX = 25.0f; // The Maximum Size of the explosion's radius.
	float m_altitude = 0.0f; // The Maximum distance the player's beam can go up.
	float m_distanceBetween = 0.0f; // The Distance between the Asteroid and the Explosion's Centre.
	int m_enemyCooldown = 1; // How long it takes for the asteroid to come back.
	int m_newCooldown = 20; 
	// Decrements when the player makes a successful hit, making the asteroid spawn faster.
	int m_score = 0; // The Player's current score
	int m_scoreToGain = 0; // The Score the player will gain
	int m_extraCooldown = 0;


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

