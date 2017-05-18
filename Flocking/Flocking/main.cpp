#include <SFML/Graphics.hpp>
#include "VehicleManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking");
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;
	VehicleManager vm;

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				vm.addVehicle(window.mapPixelToCoords(mouse));
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				vm.removeVehicle();
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				vm.toggle_flock();
			}
		}

		// update vehicles
		vm.update(window.mapPixelToCoords(mouse), clock.restart());

		window.clear();
		window.draw(vm);
		window.display();
	}

	return 0;
}
