#pragma once
#include "Framework/Actor.h"
#include <Core/Transform.h>
#include <Renderer/Model.h>

class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;
	virtual void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};