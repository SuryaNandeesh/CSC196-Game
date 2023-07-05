#pragma once
#include "../ThirdParty/SDL2-2.28.1/include/SDL.h"
#include <string>

namespace kiko
{
	void CreateWindow(const std::string& title, int width, int height);

	class Renderer 
	{
	public:
		Renderer() = default;
		~Renderer() = default;
		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(int r, int g, int b, int a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawPoint(int x, int y);

		int GetHeight() const { return m_height; }
		int GetWidth() const { return m_width; }

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr ;
		SDL_Window* m_window = nullptr;
	};
}