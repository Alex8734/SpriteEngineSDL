#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ImGui/ImGUISFML.h>


namespace spe
{
	class Vector2
	{
	public:
		float x, y;

		Vector2();
		Vector2(float x, float y);
		Vector2(const ImVec2& vec);
		Vector2(const spe::Vector2& rhs);
		Vector2(const sf::Vector2f& rhs);

		bool operator==(const Vector2& rhs);
		bool operator!=(const Vector2& rhs);
		spe::Vector2 operator+=(const spe::Vector2& rhs);
		spe::Vector2 operator*(const float& rhs);
		spe::Vector2 operator-(const spe::Vector2& rhs);
		spe::Vector2 operator+(const spe::Vector2& rhs);
		spe::Vector2 operator*=(const spe::Vector2& rhs);
		spe::Vector2 operator/=(const spe::Vector2& rhs);
		spe::Vector2 operator/=(const float rhs);
		spe::Vector2 operator*(const spe::Vector2& rhs);

		friend std::ostream& operator<<(std::ostream& os, const spe::Vector2& rhs);

	public:
		static const spe::Vector2 SCREEN_MIDDLE;
		static ImVec2 toImVec2(const spe::Vector2& vec);
		static sf::Vector2f toSFVector(const spe::Vector2& vec);
	};

	std::ostream& operator<<(std::ostream& os, const spe::Vector2& rhs);
}