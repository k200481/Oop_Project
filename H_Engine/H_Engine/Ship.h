#pragma once

#include "Vec2.h"
#include "Animation.h"
#include "BasicEntity.h"

#include <vector>

class Ship : public BasicEntity
{
public:
	Ship(float initial_x, float initial_y, Graphics* graphics);
	Ship(const Vec2& initial_position, Graphics* graphics);

	// update position and animation
	void Update(float deltatime);
	// draw the ship
	void Draw();

	// override to rebound on impact
	bool ProcessWallCollision(const _Rect& walls) override;

	// updates the velocity of the ship
	void SetVelocity(const Vec2& new_velocity);

	// get the ship's position
	Vec2 GetPosition() const;

private:
	// ship gets stuck at the wall without this
	bool isCollidingWithWall = false;

	// animation area
	const float imageScale = 2.0f;
	// list of files to load image from
	static const std::vector<LPCWSTR> files;
	Animation animation;
};

