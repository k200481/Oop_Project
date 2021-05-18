#pragma once
#include "BasicEntity.h"

// anything that acts like a projectile, basically
class Projectile : public BasicEntity
{
public:
	// for use in cases where non-projectiles experience projectile motion
	static float GetDownwardAcceleration() {
		return DownwardAcceleration;
	}

protected:
	// protected constructors, although though it's not necessary
	Projectile(const Vec2& position = { 0.0f, 0.0f }, const Vec2& velocity = { 0.0f, 0.0f })
		:
		BasicEntity(position, velocity)
	{}
	void UpdatePosition(float deltatime) override {
		// initial position
		const Vec2 pos = GetPosition();
		// initial velocity
		const Vec2 u = GetVelocity();
		// final velocity
		const Vec2 v = u + (DownwardAccelerationVec * deltatime);
		
		// x increases normally
		const float dx = u.x * deltatime;
		// s = ut + 0.5 at^2
		const float dy = u.y * deltatime + 0.5f * (DownwardAcceleration * deltatime * deltatime);

		// new velocity is just v (the final velocity calculated)
		BasicEntity::SetVelocity(v);
		// new position is the original position + delta_position
		BasicEntity::SetPosition(pos + Vec2(dx, dy));
	}

private:
	// pixels / sec^2
	static constexpr float DownwardAcceleration = 100.0f;
	const Vec2 DownwardAccelerationVec = {0.0f, DownwardAcceleration};
};

