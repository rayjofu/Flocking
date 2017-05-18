#pragma once
#include <SFML/Graphics.hpp>

class Vehicle : public sf::Drawable, public sf::Transformable {
public:
	Vehicle(float x, float y);
	sf::ConvexShape triangle;
	void update(sf::Vector2f dest, sf::Time elapsed);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void separate(std::vector<Vehicle> vehicles);
	sf::Vector2f align(std::vector<Vehicle> vehicles);
	sf::Vector2f cohesion(std::vector<Vehicle> vehicles);
private:
	sf::Vector2f location;
	sf::Vector2f velocity;
	
	sf::Vector2f acceleration;
	float maxSpeed;
	float maxForce;
	
	sf::Vector2f normalize(sf::Vector2f vector);
	sf::Vector2f limit(sf::Vector2f vector, float max);	
	sf::Vector2f seek(sf::Vector2f target);
	void applyForce(sf::Vector2f force);
};