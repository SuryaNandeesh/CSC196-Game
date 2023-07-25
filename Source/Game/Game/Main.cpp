#include "Core/Core.h"
#include "Renderer/Render.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"
#include "Player.h"
#include "Enemy.h"

#include"Starfield.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>

using namespace std;
//using vec2 = kiko::Vector2; <- aliases tutorial

class Star
{
public:
	Star(kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(kiko::Renderer& g_renderer)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= kiko::g_renderer.GetWidth()) m_pos.x = 0;
		if (m_pos.y >= kiko::g_renderer.GetHeight()) m_pos.y = 0;
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

//ctrl +k +c = ez comment

int main(int argc, char* argv[])
{
	{
		//std::unique_ptr<int> up = std::make_unique<int>(10);
	}

	kiko::MemoryTracker::Initialize();

	int m1 = kiko::Max(4.0f, 3.0f);
	int m2 = kiko::Max(4, 3);

	constexpr float a = kiko::DegToRad(180.0f);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("Assets");
	kiko::Renderer g_renderer;

	int* p = new int;
	delete p;
	g_renderer.Initialize();
	g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();

	kiko::g_audiosystem.Initialize();
	kiko::g_audiosystem.AddAudio("metal pipe", "metal_pipe.wav");

	unique_ptr<Starfield> game = make_unique<Starfield>();
	game->Initialize();

	//std::vector<kiko::vec2> points{ {10, -5}, { 0,0}, { 10, 5 } };

	vector<Star> stars;
	for (int i = 1; i <= 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::randomf(kiko::g_renderer.GetWidth()), kiko::randomf(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 400), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	kiko::Transform transform{ {400, 300}, 0, 3};

	kiko::vec2 position{400, 300};
	float speed = 1000;
	constexpr float turnRate = kiko::DegToRad(180.0f);

	kiko::Scene scene;
	unique_ptr<Player> player = make_unique<Player>( 200.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0 , 6 }, kiko::g_manager.Get("ship.txt"));
	player->m_tag = "Player";
	scene.Add(std::move(player));
	//Player player{ 200, kiko::Pi, { { 400, 300 }, 0 , 6 }, model };
	for (int i = 0; i < 1000; i++) {
		unique_ptr<Enemy> enemy = make_unique<Enemy>( kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { 400, 300 }, kiko::randomf(kiko::TwoPi), 6}, kiko::g_manager.Get("ship.txt"));
		enemy->m_tag = "Enemy";
		scene.Add(std::move(enemy));
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::AudioSystem().Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		//update game
		scene.Update(kiko::g_time.GetDeltaTime());
		
		//movement
		kiko::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		position += direction * speed * kiko::g_time.GetDeltaTime();

		if (kiko::InputSystem().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::AudioSystem().PlayOneShot("metal_pipe");
		}

		//button click
		if (kiko::g_inputSystem.GetMouseButtonDown(0))
		{
			cout << "\nLeft Mouse Button Clicked!" << endl;

			cout << "\nMouse Position X: " << kiko::g_inputSystem.GetMousePosition().x << "\nMouse Position Y: " << kiko::g_inputSystem.GetMousePosition().y << endl;
		}

		g_renderer.SetColor(0, 0, 0, 0);
		g_renderer.BeginFrame();
		//draw
		for (auto& star : stars) {

			star.Update(kiko::g_renderer);
			if (star.m_pos.x >= kiko::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= kiko::g_renderer.GetHeight()) star.m_pos.y = 0;

			g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), kiko::random(256));
			g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}
		scene.Draw(kiko::g_renderer);
		game->Draw(kiko::g_renderer);
		g_renderer.EndFrame();
	}
	scene.RemoveAll();
	kiko::MemoryTracker::Initialize();
	return 0;
}

