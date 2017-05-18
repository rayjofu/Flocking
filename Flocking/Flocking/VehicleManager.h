#pragma once
#include "Vehicle.h"
#include <vector>

class VehicleManager : public sf::Drawable, public sf::Transformable {
public:
	VehicleManager();
	bool isFlocking;
	void update(sf::Vector2f dest, sf::Time elapsed);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addVehicle(sf::Vector2f vector);
	void removeVehicle();
	void toggle_flock();
private:
	std::vector<Vehicle> vehicles;
};