// Author: Joshua Dunne
// Date(s): 8/11/18, 13/11/18, 16/11/18
// Estimated Time to finish: ~8 Hours
// Actual Time Taken: 7 Hours
// Details: Various programs that perform different vector calculations, each with a specific use.


#include "MyVector2.h"


/// <summary>
/// Square Root of X ^ 2 + Y ^ 2
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x ) + (t_vector.y * t_vector.y); // X^2 + Y^2
	const float length = sqrt(sumOfSquares); //Square Root of X ^ 2 + Y ^ 2
	return length;
}

// X^2 + Y^2
float vectorLengthSquared(sf::Vector2f t_vector)
{
	float lengthOfVector = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y); // X^2 + Y^2
	return lengthOfVector;
}

// Gets the Cross Product of 2 vectors.
float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_vectorB)
{
	float crossProduct = (t_vectorB.x * t_vectorA.x) - (t_vectorB.y * t_vectorA.y); // Vx * Ux - Vy * Uy
	return crossProduct;
}

 // Gets the dot product of two vectors.
float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_vectorB)
{
	float dotProduct = (t_vectorB.x * t_vectorA.x) + (t_vectorB.y * t_vectorA.y); // Vx * Ux + Vy * Uy
	return dotProduct;
}

// Get the Angle that Two Vectors make.
float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_vectorB)
{
	float dotProduct = vectorDotProduct(t_vectorA, t_vectorB); // Gets the Dot Product
	float magnitudeA = vectorLength(t_vectorA); // Gets the Magnitude of Vector A
	float magnitudeB = vectorLength(t_vectorB); // Gets the Magnitude of Vector B
	const float ANGLE = acosf(dotProduct / (magnitudeA * magnitudeB) ) * (180 / PI); 
	// Gets the Angle using cos-1, multiplied by 180/PI to convert to Angle
	return ANGLE;
}

// Rotate a Vector by a certain amount of Radians.
sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	// You will need to put your calculator in Radians mode to proof-check this.

	sf::Vector2f newVectorRotation = { 0,0 };
	newVectorRotation.x = (t_vector.x * cos(t_angleRadians)) - (t_vector.y * sin(t_angleRadians)); // X * Cos(Radians) - Y * Sin(Radians)
	newVectorRotation.y = (t_vector.x * sin(t_angleRadians)) + (t_vector.y * cos(t_angleRadians)); // X * Sin(Radians) - Y * Cos(Radians)
	return newVectorRotation;
}

// Find the projection of a Vector
sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f projectedVector = {0,0};
	float dotProduct = vectorDotProduct(t_vector, t_onto);  // Call a previously made function to get the Dot Product.
	float ontoMagnitude = vectorLength(t_onto); // Call a previously made function to get the length.
	projectedVector = (dotProduct / ontoMagnitude) * (t_onto / ontoMagnitude);
	return projectedVector;
}

// Find the rejection of a Vector (the leftovers of a projection).
sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	// Rejection = Original Vector - Projection

	sf::Vector2f projectedVector = vectorProjection(t_vector, t_onto); // Call a previously made function to get the projection.
	sf::Vector2f rejectedVector = t_vector - projectedVector; // Gets the rejection of the vector.
	return rejectedVector;
}

// Find the Scalar Projeciton of a Vector.
float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	// Scalar Projection = Magnitude of t_vector's projection
	sf::Vector2f projectedVector = vectorProjection(t_vector, t_onto); // Call a previously made function to get the projection.
	float scalarProjection = vectorLength(projectedVector); // Gets magnitude of projected Vector.	
	return scalarProjection;
}

// Gets the Unit Vector.
sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	// t_vector / t_vector's magnitude
	float vectorMagnitude = vectorLength(t_vector); // Call a previously made function to get the length of a vector.
	sf::Vector2f unitVector = t_vector / vectorMagnitude; //  Gets the unit vector.
	// If the original vector is multiplied by the unit vector, it will result as 1.
	return unitVector;
}
