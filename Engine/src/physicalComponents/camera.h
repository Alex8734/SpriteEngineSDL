#pragma once

#include <SFML/Graphics.hpp>
#include <calculationComponents/vector2.h>
#include <spriteComponents/stransform.h>

namespace s2d
{
	class Camera
	{
	private:

		sf::RenderWindow* ptr_renderWindow_to_engine;

		s2d::Vector2 getDefaultPosition();

	public:
		s2d::Transform transform;
		sf::View camera_view;
		float camera_zoom;
		float camera_speed;

		Camera();
		Camera(sf::RenderWindow* ptr);

		void reset();
		void update();
	};
}