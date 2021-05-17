#pragma once

#include "BasicEntity.h"
#include "Animation.h"

#include "Vec2.h"
#include <vector>

class Ninja : public BasicEntity
{
private:
	enum class State {
		Running,
		Jumping,
		Idle
	};

public:
	// constructors
	Ninja(float initial_x, float initial_y, Graphics* graphics);
	Ninja(const Vec2& initial_position, Graphics* graphics);
	
	
	// update position of ninja based on current velocity given deltatime
	void Update(float deltatime);
	
	// update velocity based on given acceleration and deltatime
	void UpdateVelocity(const Vec2& delta_velocity);
	// handles the mess that is jump physics
	void Jump();

	// draw sprite
	void Draw();
	// getters and setters
	// get position
	Vec2 GetPosition() const;
	// get velocity
	Vec2 GetVelocity() const;
	// set velocity
	void SetVelocity(const Vec2& new_velocity);
	// check if ninja is in mid-air
	bool IsInAir() {
		return state == State::Jumping;
	}

private:
	void UpdateStateAndDirection(const Vec2& v);
private:
	State state = State::Idle;
	Animation::Direction direction = Animation::Direction::Right;

	// animation management
	const float imageScale = 0.2f;

	// all types of animations
	std::vector<Animation> animations;

	static const std::vector<LPCWSTR> run_files;
	static const std::vector<LPCWSTR> idle_files;
};

