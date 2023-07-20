#pragma once
#include "Framework/Actor.h"
#include <Core/Transform.h>
#include <Renderer/Model.h>


class Enemy : public kiko::Actor
{
public:
	Enemy(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireTime = 2.0f;
		m_fireTimer = m_fireTime;
	}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireTime = 0;
	float m_fireTimer = 0;
};

