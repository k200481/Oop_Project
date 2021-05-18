#pragma once
#include "Projectile.h"
#include "Animation.h"

class Kunai : public Projectile
{
public:
	//constructor
	Kunai(const Vec2& position, const Vec2& velocity, Graphics* graphics);

	// update position and animation
	void Update(float deltatime);
	// override process wall collision
	bool ProcessWallCollision(const _Rect& walls) override;

	// used to destroy bullet
	void SetDestroyed();
	// returns true if bullet has been destroyed
	bool IsDestroyed() const;
	// draws bullet depending on its position
	void Draw();

	// getters and setters
	Vec2 GetPosition() const;

	// gotta override these

	void OnResetDevice() override;
	void OnLostDevice() override;

private:
	//
	bool isDestroyed = false;

	// drawing related
	// animation files
	static const std::vector<LPCWSTR> file;
	float imageScale = 1.0f;
	float degrees = 270.0f;
	Animation animation;
};

