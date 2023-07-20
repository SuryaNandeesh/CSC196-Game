#include "Enemy.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Renderer/Render.h"
#include "Player.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player) {
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;
	}

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	m_fireTime -= dt;
	if (m_fireTimer = 0) {
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1.0f };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, 2.0f, transform, m_model);
		m_scene->Add(weapon);
	}
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "Player_Bullet") {
		m_destroyed = true;
	}
}
