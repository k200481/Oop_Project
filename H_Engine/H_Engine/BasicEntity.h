#pragma once

#include "Vec2.h"
#include "_Rect.h"

// anything that has a position, can move, and collide with other things
// a simple rectangle
class BasicEntity
{
public:
	// just returs true or false
	bool DetectEntityCollision(const BasicEntity& other) const;
	// returns true when there is a collision
	// bonds entity within the walls
	// can be overridden to also rebound the entity
	virtual bool ProcessWallCollision(const _Rect& walls);
	// get the center of the entity
	Vec2 GetCenter() const;

protected:
	// protected constructors so class becomes abstract
	BasicEntity();
	BasicEntity(const Vec2& position);
	BasicEntity(const Vec2& position, const Vec2& velocity);

protected:
	// get rect to detect collisions
	_Rect GetRect() const;
	// update position based on current velocity
	void UpdatePosition(float deltatime);

	// getters and setters
	// get current position
	Vec2 GetPosition() const;
	// get current velocity
	Vec2 GetVelocity() const;
	// set position, can be overrided to have some additional effect
	virtual void SetPosition(const Vec2& position);
	// set velocity, can be overrided to have some additional effect
	virtual void SetVelocity(const Vec2& velocity);
	// width and height must be initialized using these,
	// as it's not possible at runtime through the parameterized constructors
	void SetWidth(float width);
	void SetHeight(float height);
	float GetWidth();
	float GetHeight();

private:
	Vec2 position = {0.0f,0.0f};
	Vec2 velocity = { 0.0f,0.0f };
	float width = -1.0f;
	float height = -1.0f;
};

