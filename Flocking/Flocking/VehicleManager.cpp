#include "VehicleManager.h"
#include <iostream>

VehicleManager::VehicleManager()
{
	vehicles.push_back(Vehicle(0.f, 0.f));
	isFlocking = true;
}

void VehicleManager::update(sf::Vector2f dest, sf::Time elapsed)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		if (isFlocking)
		{
			vehicles[i].separate(vehicles);
			vehicles[i].align(vehicles);
			vehicles[i].cohesion(vehicles);
		}
		vehicles[i].update(dest, elapsed);
	}
}

void VehicleManager::toggle_flock()
{
	isFlocking = !isFlocking;
	if (isFlocking)
	{
		std::cout << "Forces enabled" << std::endl;
		return;
	}
	
	std::cout << "Forces disabled" << std::endl;
}

void VehicleManager::addVehicle(sf::Vector2f vector)
{
	vehicles.push_back(Vehicle(vector.x, vector.y));
	std::cout << "Total vehicles: " << vehicles.size() << std::endl;
}

void VehicleManager::removeVehicle()
{
	if (vehicles.size() != 0)
	{
		vehicles.pop_back();
		std::cout << "Total vehicles: " << vehicles.size() << std::endl;
	}
}

void VehicleManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Vehicle v : vehicles)
	{
		// apply transform
		states.transform *= v.getTransform();

		// assign texture
		states.texture = NULL;

		// draw vertex array
		target.draw(v.triangle, states);
	}
}