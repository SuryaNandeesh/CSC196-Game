#include "Starfield.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Render.h"
#include "Renderer/ModelManager.h"
//include the text thingy too

bool SpaceGame::Initialize()
{
	//stuff from making the text + score

	//audio
	kiko::g_audiosystem.AddAudio("metal pipe", "metal_pipe.wav");

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::StartGame:
		break;
	case SpaceGame::StartLevel:
	{
		//player
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 6 }, kiko::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		m_scene->Add(std::move(player));
	}
		break;
	case SpaceGame::Game:
		break;
	case SpaceGame::PlayerDead:
		
		break;
	case SpaceGame::GameOver:
		break;
	default:
		break;
	}
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
