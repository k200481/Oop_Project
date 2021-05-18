#pragma once

#include "Vec2.h"
#include "Animation.h"
#include "BasicEntity.h"
#include "Bullet.h"

#include <vector>

class Ship : public BasicEntity
{
public:
	Ship(float initial_x, float initial_y, Graphics* graphics);
	Ship(const Vec2& initial_position, Graphics* graphics);

	// update position and animation
	void Update(float deltatime);

	// returns true if a given amount of time has passed since the last fire
	bool CanFire();
	// returns a pointer to dynamically allocated bullet, as it's faster this way
	Bullet* Fire();

	// draw the ship
	void Draw();

	// override to rebound on impact
	bool ProcessWallCollision(const _Rect& walls) override;

	// updates the velocity of the ship
	void SetVelocity(const Vec2& new_velocity);

	// get the ship's position
	Vec2 GetPosition() const;

	// gotta override these

	void OnResetDevice() override;
	void OnLostDevice() override;

private:
	// ship gets stuck at the wall without this
	bool isCollidingWithWall = false;

	// firing
	// amount of time that has to pass until shipcan fire again
	const float firePeriod = 2.0f;
	// amount of time that has passed since the last fire
	float fireTimePassed = 0.0f;
	// temporarily storing graphics here, will figure out a way to avoid ding so later... maybe
	// needed to fire bullets
	Graphics* graphics = NULL;

	// might make a projectile manager class that deals with an entitie's projectiles

	// animation area
	const float imageScale = 2.0f;
	// list of files to load image from
	static const std::vector<LPCWSTR> files;
	Animation animation;
};

