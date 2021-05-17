#pragma once

#include "BasicEntity.h"
#include "Animation.h"
#include "Vec2.h"

class Bullet : public BasicEntity
{
public:
	//constructor
	Bullet(const Vec2& position, const Vec2& velocity, Graphics* graphics);

	// update position and animation
	void Update(float deltatime);
	// override process wall collision
	bool ProcessWallCollision(const _Rect& walls) override;

	// used to destroy bullet
	void BulletDestroyed();
	// returns true if bullet has been destroyed
	bool IsDestroyed() const;
	// draws bullet depending on its position
	void Draw();

	// getters and setters
	Vec2 GetPosition() const;

private:
	// delete the bullet when this becomes true
	bool isDestroyed = false;

	// animation info
	static const std::vector<LPCWSTR> file;
	const float degrees = 270.0f;
	const float imageScale = 1.0f;
	Animation animation;
};