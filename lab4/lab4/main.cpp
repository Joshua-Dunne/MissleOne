// Author: Joshua Dunne
// C00241588
// Date(s): 22/11/18, 26/11/18, 29/11/18, 30/11/18, 02/12/18, 04/12/18, 06/12/18, 07/12/18, 09/12/18
// Estimated Time: 14 Hours
// Actual Time: 15 Hours

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include "game.h"
#include <stdlib.h>



/// <summary>
/// main entry point
/// </summary>
/// <returns>zero</returns>
int main()
{
#ifdef DEBUG
	srand(static_cast<unsigned int>(time(nullptr))); // If in Release mode, have a random Debug Seed.
#else
	srand(10u); // If in Debug Mode, keep the same Debug Seed.
#endif// DEBUG

	Game game;
	game.run();
	return 0;
}