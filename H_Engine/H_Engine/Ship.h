#pragma once

#include "Vec2.h"
#include "textureManager.h"
#include "image.h"

#include "Animation.h"

#include <vector>

class Ship
{
public:
	Ship(float initial_x, float initial_y, Graphics* graphics);
	Ship(const Vec2& initial_position, Graphics* graphics);

	// update position and animation
	void Update(float deltatime);
	// draw the ship
	void Draw();

	// updates the velocity of the ship
	void SetVelocity(const Vec2& new_velocity);
	// updates the direction of the ship while keeping movement speed constant
	void SetDirection(const Vec2& new_direction);

	// get the ship's position
	Vec2 GetPosition() const;
	Vec2 GetDirection() const;
	float GetMovementSpeed() const;
private:
	
private:
	// position
	Vec2 position;
	// velocity, also tracks direction
	Vec2 direction = { 1.0f,0.0f };
	// movement speed, 5.0f by default
	float movementSpeed = 5.0f;

	// drawing related
	int currentFrame = 0;
	static constexpr int frameCount = 5;
	static constexpr float holdDuration = 0.1f;
	float heldFor = 0.0f;
	std::vector<TextureManager> texManager;
	std::vector<Image> image;
	const float imageScale = 2.0f;

	// list of files to load image from
	static const std::vector<LPCWSTR> files;
	Animation animation;
};

