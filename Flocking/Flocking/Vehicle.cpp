#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle(float x, float y)
{
	location = sf::Vector2f(x, y);

	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(-10, -15));
	triangle.setPoint(1, sf::Vector2f(10, -15));
	triangle.setPoint(2, sf::Vector2f(0, 15));
	triangle.setPosition(location);
	
	velocity = sf::Vector2f(triangle.getPoint(2) - location);
	acceleration = sf::Vector2f(0, 0);

	maxSpeed = 100.f;
	maxForce = 0.1f;
}

sf::Vector2f Vehicle::normalize(sf::Vector2f vector)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);
	return sf::Vector2f(vector.x / length, vector.y / length);
}

void Vehicle::update(sf::Vector2f dest, sf::Time elapsed)
{
	velocity = limit(velocity + acceleration, maxSpeed);
	location += velocity * elapsed.asSeconds();
	triangle.setPosition(location);
	triangle.setRotation(atan2f(velocity.y, velocity.x) * 180.f / 3.14159365 - 90.f);

	acceleration *= 0.f;
	seek(dest);
}

sf::Vector2f Vehicle::limit(sf::Vector2f vector, float max_length)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length > max_length)
	{
		vector = sf::Vector2f(vector.x / length, vector.y / length);
	}

	return vector;
}


sf::Vector2f Vehicle::seek(sf::Vector2f target)
{
	sf::Vector2f desired = normalize(target - location) * maxSpeed;
	sf::Vector2f steer = limit(desired - velocity, maxForce);
	applyForce(steer);
	return steer;
}

void Vehicle::applyForce(sf::Vector2f force)
{
	acceleration += force;
}

void Vehicle::separate(std::vector<Vehicle> vehicles)
{
	float desiredSeparation = 20.f;
	sf::Vector2f sum;
	int count = 0;

	for (Vehicle other : vehicles)
	{
		sf::Vector2f temp = other.location - location;
		float d = sqrt(temp.x * temp.x + temp.y * temp.y);
		if ((d > 0) && (d < desiredSeparation))
		{
			sf::Vector2f diff = normalize(location - other.location) / d;
			sum += diff;
			count++;
		}
	}

	if (count > 0)
	{
		sum /= 1.f * count;
		sum = normalize(sum) * maxSpeed;
		sf::Vector2f steer = limit(sum - velocity, maxForce);
		applyForce(steer);
	}
}

sf::Vector2f Vehicle::align(std::vector<Vehicle> vehicles)
{
	float neighbordist = 50;
	sf::Vector2f sum;
	int count = 0;
	for (Vehicle other : vehicles)
	{
		sum += other.velocity;
		count++;
	}

	if (count > 0)
	{
		sum /= 1.f * count;
		sum = normalize(sum) * maxSpeed;

		sf::Vector2f steer = limit(sum - velocity, maxForce);
		return steer;
	}
	
	return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Vehicle::cohesion(std::vector<Vehicle> vehicles)
{
	float neighbordist = 50;
	sf::Vector2f sum;
	int count = 0;
	for (Vehicle other : vehicles)
	{
		sf::Vector2f temp = location - other.location;
		float d = sqrt(temp.x * temp.x + temp.y * temp.y);
		if ((d > 0) && (d < neighbordist))
		{
			sum += other.location;
			count++;
		}
	}

	if (count > 0)
	{
		sum /= 1.f * count;
		return seek(sum);
	}

	return sf::Vector2f(0.f, 0.f);
}

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply transform
	states.transform *= getTransform();

	// assign texture
	states.texture = NULL;

	// draw vertex array
	target.draw(triangle, states);
}