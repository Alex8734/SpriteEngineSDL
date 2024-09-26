#pragma once

#include <ImGui/imgui_impl_sdlrenderer2.h>
#include <ImGui/imgui.h>

#include <SDL.h>

#include "Camera/Camera.h"
#include "Core/Event.h"
#include "Sprite/Components/Light/LightRepository.h"
#include "Sprite/Sprite.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace spe
{
	class GameWindow
	{
	private:
		SDL_Window* m_ptr_Window;
        SDL_Renderer* m_ptr_Renderer;
		spe::Camera* m_Camera;
		spe::Vector2 m_Size;
		spe::Vector3* m_BackgroundColor;
		bool m_IsOpen;
		SDL_Rect m_WindowBounds;
		void UpdateCamera();

	public:
		SDL_Event WindowEvent;
		spe::Event Event;

		GameWindow();
		GameWindow(const spe::Vector2& size, const std::string& name);

		void PollEvents();
		bool IsOpen() const noexcept { return this->m_IsOpen; }
		void Draw(spe::Sprite* ptr, const sf::Shader* shader, bool ignoreLight);
		void Display();
		void Clear();
		void Shutdown();

		bool ContainsCursor();

		SDL_Window* GetRenderWindow() noexcept { return this->m_ptr_Window; }
        SDL_Renderer* GetRenderer() noexcept { return this->m_ptr_Renderer; }
		void SetCamera(spe::Camera* camera) noexcept { this->m_Camera = camera; }
		void SetBackgroundColor(spe::Vector3* bck) noexcept { this->m_BackgroundColor = bck; }
	};
}