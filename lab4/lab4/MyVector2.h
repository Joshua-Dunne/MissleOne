// author Peter Lowe
// don't edit this file
#ifndef MY_VECTOR2
#define MY_VECTOR2

#include <SFML/Graphics.hpp>



float vectorLength(const sf::Vector2f t_vector);  // root x2 + y2
float vectorLengthSquared(const sf::Vector2f t_vector); // x2 + y2
sf::Vector2f vectorUnitVector(sf::Vector2f t_vector);// length of ans is one, null in null out
float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_vectorB);  // Vx * Uy - Vy * Ux
float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_vectorB);  // Vx * Uy + Vy * Ux
float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_vectorB); // result always 0>= && <=180
sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians); // anti-clockwise ({1,0},PI/2) = {0,1}
sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto);// ans parallel to second vector
sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto);// ans perpendicular to second vector
float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto);// scalar resolute



const float PI = 3.14159265359f;



#endif  // MY_VECTOR2